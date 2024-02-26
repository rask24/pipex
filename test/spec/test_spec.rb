# frozen_string_literal: true

require "open3"
require_relative "./spec_helper"

RSpec.describe("pipex") do
  let(:infile_path) { "test/spec/fixture/std_infile" }
  let(:outfile_path) { "test/spec/fixture/std_outfile" }

  it "executes pipex command correctly" do
    bash_command = "./pipex #{infile_path} 'cat' 'cat -e' #{outfile_path}"
    command = "bash -c \"#{bash_command}\""
    _, _, status = Open3.capture3(command)

    outfile_content = File.read(outfile_path)
    expected_content = "Hello$\nWorld$\nThis$\nis$\n42$\nTokyo$\n"

    expect(outfile_content).to(eq(expected_content))
    expect(status.exitstatus).to(eq(0))
  end

  it "execute first command error case" do
    bash_command = "./pipex #{infile_path} 'ccc' 'cat -e' #{outfile_path}"
    command = "bash -c \"#{bash_command}\""
    _, stderr, status = Open3.capture3(command)

    outfile_content = File.read(outfile_path)
    expected_content = ""

    expect(outfile_content).to(eq(expected_content))
    expect(stderr).to(eq("pipex: ccc: command not found\n"))
    expect(status.exitstatus).to(eq(0))
  end

  it "execute second command error case" do
    bash_command = "./pipex #{infile_path} 'cat' 'ccc -e' #{outfile_path}"
    command = "bash -c \"#{bash_command}\""
    _, stderr, status = Open3.capture3(command)

    outfile_content = File.read(outfile_path)
    expected_content = ""

    expect(outfile_content).to(eq(expected_content))
    expect(stderr).to(eq("pipex: ccc: command not found\n"))
    expect(status.exitstatus).to(eq(127))
  end

  it "execute error case" do
    bash_command = "./pipex #{infile_path} 'ddd' 'ccc' #{outfile_path}"
    command = "bash -c \"#{bash_command}\""
    _, stderr, status = Open3.capture3(command)

    outfile_content = File.read(outfile_path)
    expected_content = ""

    expect(outfile_content).to(eq(expected_content))
    expect(stderr).to(eq("pipex: ddd: command not found\npipex: ccc: command not found\n"))
    expect(status.exitstatus).to(eq(127))
  end
end
