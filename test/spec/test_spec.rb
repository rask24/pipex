# frozen_string_literal: true

require "open3"
require_relative "./spec_helper"

RSpec.describe("pipex") do
  let(:infile_path) { "test/spec/fixture/std_infile" }
  let(:outfile_path) { "test/spec/fixture/std_outfile" }
  let(:space_infile_path) { "test/spec/fixture/space infile" }
  let(:ft_infile_path) { "test/spec/fixture/ft_infile" }

  def execute_command(bash_command)
    command = ["bash", "-c", bash_command]
    Open3.capture3(*command)
  end

  def read_outfile
    File.read(outfile_path)
  end

  def clean_outfile
    File.truncate(outfile_path, 0)
  end

  describe "command execution" do
    context "with valid commands" do
      it "executes a simple pipex command" do
        # ./pipex infile cat cat outfile
        _, _, status = execute_command("./pipex #{infile_path} 'cat' 'cat -e' #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "handles absolute path commands" do
        # ./pipex infile /bin/cat /bin/cat outfile
        _, _, status = execute_command("./pipex #{infile_path} /bin/cat '/bin/cat -e' #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "handles infile including a space" do
        # ./pipex "space infile" cat cat outfile
        _, _, status = execute_command("./pipex \"#{space_infile_path}\" cat cat #{outfile_path}")

        expect(read_outfile).to(eq("This\nfile\nincludes\na\nspace\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "handles relative path commands" do
        # ./pipex infile ../../../../../../../../../../bin/cat '/bin/cat -e' outfile
        _, _, status =
          execute_command("./pipex #{infile_path} ../../../../../../../../../../bin/cat '/bin/cat -e' #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "executes a script" do
        # ./pipex infile ./test/spec/fixture/cat.sh 'cat -e' outfile
        _, _, status = execute_command("./pipex #{infile_path} ./test/spec/fixture/cat.sh 'cat -e' #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "handles command with single quotation" do
        # ./pipex 42_infile "grep 'By: reasuke'" 'cat -e' outfile
        _, _, status = execute_command("./pipex #{ft_infile_path} \"grep 'By: reasuke'\" cat #{outfile_path}")

        expect(read_outfile).to(
          eq("/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */\n"),
        )
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "handles command with double quotation" do
        # ./pipex 42_infile "grep 'By: reasuke'" 'cat -e' outfile
        _, _, status = execute_command("./pipex #{ft_infile_path} 'grep \"By: reasuke\"' cat #{outfile_path}")

        expect(read_outfile).to(
          eq("/*   By: reasuke <reasuke@student.42tokyo.jp>       +#+  +:+       +#+        */\n"),
        )
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "executes a simple pipex command delimited by tab" do
        # ./pipex infile cat "cat -e" outfile
        _, _, status = execute_command("./pipex #{infile_path} 'cat' \"cat\t-e\" #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "executes a simple pipex command includes escaped double quotation" do
        # ./pipex infile cat 'echo "double\\\"quotation"' outfile
        _, _, status = execute_command("./pipex #{infile_path} 'cat' 'echo -n \"double\\\"quotation\"' #{outfile_path}")

        expect(read_outfile).to(eq("double\"quotation"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "executes a simple pipex command includes special charactors" do
        # ./pipex infile 'cat' 'echo -n \!\?\#\<\)' outfile
        _, _, status = execute_command("./pipex #{infile_path} 'cat' 'echo -n \!\?\#\<\)' #{outfile_path}") # rubocop:disable Style/RedundantStringEscape

        expect(read_outfile).to(eq("!?#<)"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "executes a simple pipex command includes escaped backslash" do
        # ./pipex infile cat 'echo "back\\\\slash"' outfile
        _, _, status = execute_command("./pipex #{infile_path} 'cat' 'echo -n \"back\\\\slash\"' #{outfile_path}")

        expect(read_outfile).to(eq("back\\slash"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "executes a multi pipex command" do
        # ./pipex infile cat cat cat outfile
        _, _, status = execute_command("./pipex #{infile_path} cat cat cat #{outfile_path}")

        expect(read_outfile).to(eq("Hello\nWorld\nThis\nis\n42\nTokyo\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "executes a multi pipex command" do
        # ./pipex infile cat cat cat cat cat cat 'head -n 1' cat cat cat cat cat cat cat cat outfile
        _, _, status = execute_command(
          "./pipex #{infile_path} cat cat cat cat cat cat 'head -n 1' cat cat cat cat cat cat cat cat #{outfile_path}",
        )

        expect(read_outfile).to(eq("Hello\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end
    end

    context "with errors" do
      it "reports error for first command not found" do
        # ./pipex infile 'ccc' 'cat -e' outfile
        _, stderr, status = execute_command("./pipex #{infile_path} 'ccc' 'cat -e' #{outfile_path}")

        expect(read_outfile).to(eq(""))
        expect(stderr).to(eq("pipex: ccc: command not found\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "reports error and exits with 127 for second command not found" do
        # ./pipex infile 'cat' 'ccc -e' outfile
        _, stderr, status = execute_command("./pipex #{infile_path} 'cat' 'ccc -e' #{outfile_path}")

        expect(read_outfile).to(eq(""))
        expect(stderr).to(include("pipex: ccc: command not found\n"))
        expect(status.exitstatus).to(eq(127))
        clean_outfile
      end

      it "handles not permitted script as first command" do
        # ./pipex infile ./test/spec/fixuture/not_permitted_cat.sh 'cat -e' outfile
        _, stderr, status =
          execute_command("./pipex #{infile_path} ./test/spec/fixture/not_permitted_cat.sh 'cat -e' #{outfile_path}")

        expect(stderr).to(eq("pipex: ./test/spec/fixture/not_permitted_cat.sh: Permission denied\n"))
        expect(status.exitstatus).to(eq(0))
        clean_outfile
      end

      it "handles not permitted script as second command" do
        # ./pipex infile cat ./test/spce/fixture/not_permitted_cat.sh outfile
        _, stderr, status =
          execute_command("./pipex #{infile_path} cat ./test/spec/fixture/not_permitted_cat.sh #{outfile_path}")

        expect(stderr).to(eq("pipex: ./test/spec/fixture/not_permitted_cat.sh: Permission denied\n"))
        expect(status.exitstatus).to(eq(126))
        clean_outfile
      end

      it "reports error for each command" do
        # ./pipex infile a b c d outfile
        _, stderr, status = execute_command("./pipex #{infile_path} a b c d e f g #{outfile_path}")

        expected = ""
        expected += "pipex: a: command not found\n"
        expected += "pipex: b: command not found\n"
        expected += "pipex: c: command not found\n"
        expected += "pipex: d: command not found\n"
        expected += "pipex: e: command not found\n"
        expected += "pipex: f: command not found\n"
        expected += "pipex: g: command not found\n"
        expect(stderr).to(eq(expected))
        expect(status.exitstatus).to(eq(127))
        clean_outfile
      end
    end
  end
end
