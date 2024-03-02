# frozen_string_literal: true

require "open3"
require_relative "./spec_helper"

RSpec.describe("pipex") do
  let(:infile_path) { "test/spec/fixture/std_infile" }
  let(:outfile_path) { "test/spec/fixture/std_outfile" }
  let(:space_infile_path) { "test/spec/fixture/space_infile" }

  def execute_command(bash_command)
    command = "bash -c \"#{bash_command}\""
    Open3.capture3(command)
  end

  def read_outfile
    File.read(outfile_path)
  end

  describe "command execution" do
    context "with valid commands" do
      it "executes a simple pipex command" do
        _, _, status = execute_command("./pipex #{infile_path} 'cat' 'cat -e' #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
      end

      it "handles absolute path commands" do
        _, _, status = execute_command("./pipex #{infile_path} /bin/cat '/bin/cat -e' #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
      end

      it "handles infile including a space" do
        _, _, status = execute_command("./pipex #{space_infile_path} cat cat #{outfile_path}")

        expect(read_outfile).to(eq("This\nfile\nincludes\na\nspace\n"))
        expect(status.exitstatus).to(eq(0))
      end

      it "handles relative path commands" do
        _, _, status =
          execute_command("./pipex #{infile_path} ../../../../../../../../../../bin/cat '/bin/cat -e' #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
      end

      it "executes a script" do
        _, _, status = execute_command("./pipex #{infile_path} ./test/spec/fixture/cat.sh 'cat -e' #{outfile_path}")

        expect(read_outfile).to(eq("Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"))
        expect(status.exitstatus).to(eq(0))
      end
    end

    context "with errors" do
      it "reports error for first command not found" do
        _, stderr, status = execute_command("./pipex #{infile_path} 'ccc' 'cat -e' #{outfile_path}")

        expect(read_outfile).to(eq(""))
        expect(stderr).to(include("command not found"))
        expect(status.exitstatus).to(eq(0))
      end

      it "reports error and exits with 127 for second command not found" do
        _, stderr, status = execute_command("./pipex #{infile_path} 'cat' 'ccc -e' #{outfile_path}")

        expect(read_outfile).to(eq(""))
        expect(stderr).to(include("command not found"))
        expect(status.exitstatus).to(eq(127))
      end

      it "handles not permitted script as first command" do
        _, stderr, status =
          execute_command("./pipex #{infile_path} ./test/spec/fixture/not_permitted_cat.sh 'cat -e' #{outfile_path}")

        expect(stderr).to(include("Permission denied"))
        expect(status.exitstatus).to(eq(0))
      end

      it "handles not permitted script as second command" do
        _, stderr, status =
          execute_command("./pipex #{infile_path} cat ./test/spec/fixture/not_permitted_cat.sh #{outfile_path}")

        expect(stderr).to(include("Permission denied"))
        expect(status.exitstatus).to(eq(126))
      end
    end
  end
end
