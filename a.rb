if "ABCD".sub(/(.)(.)$/, "\\1\\1") == "ABCC"
then
    puts "OK";
else
    puts "FALSE";
end

