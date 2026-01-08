import json
import sys

if(len(sys.argv) < 2):
    print("too few arguments provided")
    exit(1)

m_file = open(sys.argv[1])
file_json = json.load(m_file)
m_file.close()

for block_root in file_json.keys():
    for state in file_json[block_root]["states"]:
        def_name = block_root.replace(":", "_").upper()
        properties = state.get("properties", {})
        for prop in properties.keys():
            def_name += "__"+prop.upper()+"_"+properties[prop].upper()
            #print(properties)
        def_str = "#define " + def_name + " " + str(state["id"])
        print(def_str)
