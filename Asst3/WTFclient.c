void configureConnection(char *ip, char *port)
{
  // Write IP and Port to .configure file
  // writeToFile(".configure", ip + port thing);
}

void checkOut()
{
  // Validation checks
  // someValidationFunctions();

  // Get files from server
  // for (someFiles)
  // {
  //   requestFromServer(aFile);
  // }

  // Once files are recieved, create subdirectories in project and put files there
}

void update()
{
  // Validation checks
  // someValidationFunctions();

  // Get .manifest from server
  // requestFromServer(".manifest");

  // Once .manifest is recieved, read server's .manifest
  // readFile(serverManifest);

  // Read client .manifest
  // readFile(clientManifest);

  // Compare files and write to .update or .conflict
  // compareFiles(serverManifest, clientManifest);
}

void upgrade()
{
  // Validation checks
  // someValidationFunctions();

  // Read .update file
  // readFile(".update");

  // Apply changes to project .manifest
  // writeToFile(".manifest", data from .update);

  // Delete .update file
  // removeFile(".update");
}

void commit()
{
  // Validation checks
  // someValidationFunctions();

  // Read .manifest
  // readFile(clientManifest);

  // Get live hash of files in project, compare them to the hash in client .manifest
  // for(allFiles)
  // {
  //   getFileHash(aFile);
  //   compareHash(aFileHash, manifestHash);
  // }

  // If hash is different, write to .commit
  // writeToFile(".commit", commitData);
}

void create()
{
  // Validation checks
  // someValidationFunctions();

  // Recieve .manifest from server

  // create local project directory
  // createDirectories(project);

  // put .manifest in project directory
}

void destroy()
{
  // Validation checks
  // someValidationFunctions();

  // Check for success message
  // checkSuccess();
}

void push()
{
  // Validation checks
  // someValidationFunctions();

  // Read .commit file
  // readFile(".commit");

  // Send .commit file to server
  // sendToServer(".commit");

  // Send files to server
  // for (files in .commit)
  // {
  //   sendToServer(aFile);
  // }

  // Check for success message
  // checkSuccess();
}

void add()
{
  // Validation checks
  // someValidationFunctions();

  // Add a file to .manifest
  // writeToFile(".manifest", someData);
}

void remove()
{
  // Validation checks
  // someValidationFunctions();

  // Remove a file from .manifest
  // removeFromFile(".manifest");
}

void currentVersion()
{
  // Request project file version data from server
  // requestFromServer(versionData);

  // Print data to STDOUT
}

void history()
{
  // Validation checks
  // someValidationFunctions();

  // Request history file
  // requestFromServer(historyFile);

  // Once recieved, read history file
  // readFile(historyFile);

  // Print data to STDOUT
}

void rollback()
{
  // Validation checks
  // someValidationFunctions();

  // request version from server
  // sendVersionCommand();

  // Check success message
  // checkSuccess();
}