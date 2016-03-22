require 'fileutils'
FileUtils.mkdir_p("md")
Dir.glob("_posts/*.md") do |file|
  content = File.read(file)
  content.gsub!(/\A.*?^# /m, "# ")
  newfile = file.sub(/_posts/, "md")
  File.open(newfile, "w") do |f|
    f.write(content)
  end
end

Dir.glob("md/*.md") do |file|
  newfile = file.gsub(/\.md/, ".re")
  newfile.gsub!(/md\//, "review/")
  newfile.gsub!(/201\d-\d\d-\d\d-/, "")
  system("md2review --render-enable-cmd --parse-no-intra-emphasis #{file} > #{newfile}")
end

Dir.glob("assets/**/*.png") do |file|
  newfile = file.gsub(/assets\//, "review/images/")
  newfile.downcase!
  newfile.gsub!(/kn\//, "")
  dir = File.dirname(newfile)
  FileUtils.mkdir_p(dir)
  FileUtils.cp(file, newfile)
end

FileUtils.cp("assets/my-first-web-app/welcome_rails.png", "review/images/smallest-app/")
