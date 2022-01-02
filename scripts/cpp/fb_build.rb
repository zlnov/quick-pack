#!/usr/bin/env ruby

require 'erb'
require 'fileutils'

PROJECT_DIR = File.dirname(File.dirname(__dir__))
FLATC_PATH = "#{PROJECT_DIR}/flatbuffers/flatc"
SCHEMA_MESSAGE_PATH = "#{PROJECT_DIR}/bin/schema/message"

BUILD_TMP_DIR = "#{PROJECT_DIR}/cpp/build"

def run_command(cmd, continue)
  system cmd
  ret = $?
  if ret != 0
    puts "\nError: Command Failed:\n#{cmd}\nfailed with exit code #{ret}"
    unless continue
      abort("command failed")
    end
  end
end

def create_from_erb(filename_in, filename_out)
  unless filename_in.end_with?'.erb'
    puts "ERROR this is not a erb template"
  end
  erb_template = File.read(filename_in)

  created_file = ""
  created_file += ERB.new(erb_template, nil, '>').result()

  File.write(filename_out, created_file)
end

######## PARSE USER SCHEMA FILES ########
user_fbs=[]
user_fbs_files=[]
Dir.foreach("#{SCHEMA_MESSAGE_PATH}").each do |file|
  if file.end_with? '.fbs'
    user_fbs << file[0..-5]
    user_fbs_files << "#{SCHEMA_MESSAGE_PATH}/#{file}"
  end
end

######## make transmission schema from template ########
create_from_erb("#{PROJECT_DIR}/bin/schema/transmission.fbs.erb", "#{PROJECT_DIR}/bin/schema/transmission.fbs")

######## make transmission schema from template ########
BUILD_TMP_INCLUDE_PATH = File.join(BUILD_TMP_DIR, 'include/flatbuffers')

FileUtils.mkdir_p(BUILD_TMP_INCLUDE_PATH)

######## flatc cpp build ########
user_fbs_files.each do |fbs_file|
  run_command("#{FLATC_PATH} -c -o #{BUILD_TMP_INCLUDE_PATH} #{fbs_file}", false)
end
run_command("#{FLATC_PATH} -c -I #{SCHEMA_MESSAGE_PATH} -o #{BUILD_TMP_INCLUDE_PATH} #{PROJECT_DIR}/bin/schema/transmission.fbs", false)
