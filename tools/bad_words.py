import sys

if(len(sys.argv) < 2):
    print("too few arguments provided")
    exit(1)



f = open(sys.argv[1])
bad_words = f.readlines()
f.close()
filter_table = "char filter_list[][512] = {"
for word in bad_words:
    regex = "".join([x.strip().replace("-", "\\\\-")
                     +"+(\\\\W|_|\\\\d)*" for x in word])
    regex = "(?i)(^|[^a-zA-Z0-9])"+regex+"(?![a-zA-Z0-9])"
    line = "   \""+regex+"\", // blocks " + word
    filter_table += line
filter_table += "};"



print(filter_table)
