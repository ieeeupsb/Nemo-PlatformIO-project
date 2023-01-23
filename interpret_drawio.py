import openai
import xml.etree.ElementTree as ET

openai.api_key = "YOUR_API_KEY"
openai.api_key_path = "open_ai_api_key.txt"

def interpret_drawio(file_path):
    # Parse the XML file
    tree = ET.parse(file_path)
    diagram_string = ET.tostring(tree, encoding='unicode')

    print(diagram_string)

    # Use the OpenAI API to interpret the diagram
    response = openai.Completion.create(
        engine="text-davinci-002",
        prompt=f"Interpret the following class diagram:\n{diagram_string}\nWrite a list of there attributes and methods", 
        max_tokens=1024,
        n=1,
        stop=None,
        temperature=0.5,
    )
    
    # Print the interpretation
    print(response["choices"][0]["text"])


def write_class_code(class_info, output_folder):
    
    prompt = f"Write cpp classes with the following attributes and methods: {class_info} \n"
    print (prompt)

    # Make the API call to generate text
    response = openai.Completion.create(
        engine="text-davinci-002",
        prompt=prompt,
        max_tokens=1024,
        n=1,
        stop=None,
        temperature=0.5,
    )

    # Get the generated class code
    class_code = response["choices"][0]["text"]

        # Write the class code to a header file
    header_file_path = f"{output_folder}/class_name.h"
    with open(header_file_path, "w") as header_file:
        header_file.write("#pragma once\n")
        header_file.write(class_code)

# Example usage:
file_path = "software/doc/class-diagram.drawio.xml"

class_info = interpret_drawio(file_path)
# print (class_info)


# write_class_code(class_info, "gpt_test_folder")