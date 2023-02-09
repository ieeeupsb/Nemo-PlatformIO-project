import openai
import os

openai.api_key = "YOUR_API_KEY" 
openai.api_key_path = "open_ai_api_key.txt"

def generate_unit_tests(file_path, test_folder, function_name):

    base_file_name = os.path.splitext(os.path.basename(file_path))[0]
    test_file_name = f"{base_file_name}_test.h"
    test_file_path = os.path.join(test_folder, test_file_name)
    
    # Check if the test file exists and if the test function already exists in the file
    with open(test_file_path, "r") as test_file:
        test_file_contents = test_file.read()
        
        test_function_name = f"TEST({base_file_name}Test, {function_name}Test)"
        if test_function_name in test_file_contents:
            print(f"Test {test_function_name} already exists in {test_file_path}, skipping.")
            return
    
    function_code = ""
    inside_function = False
    function_found = False
    bracket_count = 0
    
    with open(file_path) as f:
        for line in f:
            if function_name in line and '(' in line and not function_found:
                inside_function = True
                function_found = True
                function_code += line
                bracket_count = line.count('{')
            elif inside_function:
                function_code += line
                if '{' in line:
                    bracket_count += line.count('{')
                if '}' in line:
                    bracket_count -= line.count('}')
                    if bracket_count == 0:
                        inside_function = False
                        break

    if function_found == False:
        print("No function found")
        return
    
    

    # Define the prompt
    prompt = f"Write a unit test for {function_name} in Gtests framework knowing the following code:\n{function_code}\nMake sure that the test case created is named TEST(ClassNameTest (or header_filename_test if there is no class), {function_name}Test)\n\n"
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

    # Get the generated unit tests
    generated_tests = response["choices"][0]["text"]

    if os.path.exists(test_file_path):
        with open(test_file_path, "a") as test_file:
            test_file.write(generated_tests)
    else:
        with open(test_file_path, "w") as test_file:
            test_file.write(f"#include \"{base_file_name}.h\"\n#pragma once\n")
            test_file.write("#include <gtest/gtest.h>\n")
            test_file.write(generated_tests)
        print(f"Test file created at {test_file_path}")

    print(f"Test {function_name}Test created at {test_file_path}")

# Example usage:
file_path = "lib/driver_controller/driver_controller.h" 
test_folder = "test"
function_name = "setPwm"
generate_unit_tests(file_path, test_folder, function_name)