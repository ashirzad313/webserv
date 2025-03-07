#!/usr/bin/python

import os
import cgi
import json

# Directory where the files are stored
filesystem_upload_path = "/Users/ashirzad/Desktop/w/website/upload_files/"

def list_files():
    """List files in the specified directory."""
    files = []
    for file in os.listdir(filesystem_upload_path):
        file_path = os.path.join(filesystem_upload_path, file)
        if os.path.isfile(file_path) and not file.startswith("."):
            files.append(file)
    return files

# Get the HTTP request method
form = cgi.FieldStorage()
method = os.environ.get('REQUEST_METHOD')

# Content-Type header
print("Content-Type: application/json\n")

if method == "GET":
    # List the files in the directory as a JSON response
    files = list_files()
    print(json.dumps({"files": files}))

elif method == "DELETE":
    # Process DELETE request
    resource = form.getvalue("resource")
    if resource:
        file_path = os.path.join(filesystem_upload_path, resource)
        if os.path.exists(file_path):
            os.remove(file_path)
            print(json.dumps({"message": "File deleted successfully!"}))
        else:
            print(json.dumps({"message": "Error: File not found."}))
    else:
        print(json.dumps({"message": "No file specified for deletion."}))
