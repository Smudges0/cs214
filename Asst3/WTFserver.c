void serverCheckOut()
{
  // send files to client
}

void serverUpdate()
{
  // send files to client
}

void serverCreate()
{
  // Create project folder
  // Create .manifest
  // Send .manifest to client
}

void serverDestroy()
{
  // Lock repository
  // Expire pending commits
  // Delete files and subdirectories in project directory
  // Send success message
}

void serverPush()
{
  // Recieve files from client
  // Lock repository
  // Check for stored .commit file
  // Read server .commit
  // Read client .commit
  // Compare .commit files
  // Expire pending commits
  // Duplicate project directory
  // Write or remove files to new project directory
  // Update project directory .manifest
  // Unlock repository
  // Send success message
}

void serverCurrentVersion()
{
  // Read project files + versions
  // Send data to client
}

void serverHistory()
{
  // Send history file to client
}

void serverRollback()
{
  // Get version number from client
  // Delete all versions more recent than client version request
}