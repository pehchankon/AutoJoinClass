# AutoJoinClass

1. To add a class, edit timetable.csv and add details. There are some example classes. The duration is in minutes.
2. The program is optimized to check for classes whenever the time is XX:X0
3. The above condition can be changed, in the fn configure() at line 110 the "int unit" can be changed
4. You need to allow opening zoom through browser
5. Currently recording with obs doesn't work
6. For ZOOM to function properly, check the zoom directory in the zoom.bat file
7. Run the program before class time. Eg- if class is at 10:10, then the program must be started anytime before 10:10.
8. Once started, it automatically leaves and checks for future classes and doesn't need to be restarted.

--------------------------------------------
Auto Recording through OBS requires a lot of initial setup, I'm looking for an easier way for it to work on any system easily.
I'm still working on making the joining/leaving process more efficient and practical.
