Useful links:
    https://github.com/P33a/RobotAtFactoryLite

How to contribute:
Create new branches for new features (git workflow)
Do not modify "main.cpp", use main_test.cpp instead
Use "platformio.ini" for mode configuration:
; If you want to build or upload a specific mode use
; release in build type, for testing use test in build type
; Changing here the configuration implies rebuilding the
; project, for small changes, like activating
; or deactivating the debug, go to 
; nemo_libs/nemo_global_macros.h

Git workflow:

(get the lastest version)
git checkout master (go to the main branch)
git fetch origin (download objects and refs from the repo)
git reset origin (reset the branch to origin)

(create and checkout to new branch)
git checkout -b new_feature

(update, commit and push)
git status
git add <some-file>
git commit
git push -u origin new_feature

(Pull request)
In the "Branch" menu, choose the branch that contains your commits. 
Above the list of files, click Pull request. 
Use the base branch dropdown menu to select the branch you'd like to merge your changes into, then use the compare branch drop-down menu to choose the topic branch you made your changes in.
Type a title and description for your pull request.


Setting up wifi(old):

Put your wifi credentials here:
src/udp_client/wifi_credentials_private.h

in terminal:    linux: ipconfig -> ipv4     add to setup.h
                windows: ifconfig -> inet