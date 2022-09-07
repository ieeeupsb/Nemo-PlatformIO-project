Welcome to the nemo wiki!

# Nemo

## Meetings

## Project structure:

Software:
* [PlatformIO project](sofware/pio_project/README.md):ss
* [Bluetooth app](software/bluetooth_app/README.md):ss
* [Open CV](/software/OpenCV//README.md): ss
*
Hardware:
* [Circuit](hardware/circuit/README.md)
*??

## How to contribute:
* Learn how to use the git workflow first([more about git workflow](###-git-workflow)).
* Create new branches for new features ([more about git workflow](###-git-workflow)).
* Check the README.md file for which project part.
* Use github tasks .fff

### Git workflow

1. Get the code lastest version
```
git checkout master (go to the main branch)
git fetch origin (download objects and refs from the repo)
git reset origin (reset the branch to origin)
```
2. Create new feature
```
git checkout -b new_feature
```
3. Update, commit and push
```
git status
git add <some-file>
git commit
git push -u origin new_feature
```
#### Git crendential manager
```
git config --global credential.credentialStore gpg
```
[More about Git Credential Manager](https://github.com/GitCredentialManager/)

4. Pull request <br>
    * In the "Branch" menu, choose the branch that contains your commits. 
    * Above the list of files, click Pull request. 
    * Use the base branch dropdown menu to select the branch you'd like to merge your changes into, then use the compare branch drop-down menu to choose the topic branch you made your changes in.
Type a title and description for your pull request.

### TODO Tree

## Useful links:
    https://github.com/P33a/RobotAtFactoryLite