## SATELLITE TRACKER

***Welcome to the SATELITE TRACKING SYSTEM. A terminal app which allows you to track the location of any orbiter in Earth's atmosphere***

External Libraries:
- [libpredict](<https://github.com/la1k/libpredict>)

Build System:
-CMake (v3.28)

## What the it offers:
When you start the program, you'll see a main menu with these options:

```
1. TRACK AN ORBITER
2. MY SATELLITES  
3. EXIT
```

Enter a number (1-4) and press ENTER to select an option.

------------------------------------------------------------------------------------------------------------------

## Option 1: TRACK AN ORBITER

When you select option 1, you'll be asked:

```
New orbiter?
Y/N:
```

### **If you answer Y (Yes) - Add a NEW satellite:**
1. The program will show your current folder location
2. Enter a name for the satellite (e.g., "ISS", "Hubble")
3. You'll be prompted to enter TLE data:

   ```
   TLE1:
   ```
   *Paste Line 1 of the TLE, then press ENTER*

   ```
   TLE2:
   ```
   *Paste Line 2 of the TLE, then press ENTER*

4. You'll be asked how much time you'd like the tracking to continue for (in seconds):
    - You'll get exactly one update per second

5. The program will automatically start tracking and show you:
   - Satellite position (latitude, longitude, altitude)
   - Viewing angles (azimuth, elevation)
   - Apparent elevation (corrected for atmosphere)

### **Example TLE for ISS:**
```
TLE1: 1 25544U 98067A   24343.17118056  .00017709  00000-0  32487-3 0  9995
TLE2: 2 25544  51.6408  57.8497 0003240  24.2535 336.3267 15.50169958461728
```

### **If you answer N (No):**
Returns to the main menu.

------------------------------------------------------------------------------------------------------------------

## Option 2: MY SATELLITES

This shows all saved satellites and gives you these options:

```
1.|CREATE| 2.|OPEN| 3.|DELETE| 4.|EXIT|
```

### **Option 1: CREATE**
Same as "TRACK AN ORBITER" → "Y" from the main menu.

### **Option 2: OPEN**
1. Enter the name of a saved satellite
2. The program will display its TLE data
3. Then show tracking information

### **Option 3: DELETE**
1. Enter the name of the satellite to delete
2. Confirm with Y (Yes) or N (No)
3. Returns to the satellite list

### **Option 4: EXIT**
Returns to the main menu.

------------------------------------------------------------------------------------------------------------------

## Option 3: EXIT

Closes the program and brightens up your day with the message: "See you soon :)"

------------------------------------------------------------------------------------------------------------------

### **Understanding the tracking output**

Example of what is displayed in console once you start tracking:
```
ISS
lat=51.640800, lon=57.849700, alt=415.000000
azi=145.32 (rate: 0.15), ele=25.67 (rate: -0.08)
Apparent elevation: 25.45
```

- **Observer location is FIXED** at approximately Oslo, Norway (63.9°N, 10.9°E)
- **TLE data must be current** for accurate tracking (TLEs expire after ~2 weeks)
- **The program updates every second** when tracking a satellite
- 
------------------------------------------------------------------------------------------------------------------

## Where is data saved?

All satellites are saved in a folder called `my-orbiters` in your current directory.

Each satellite is saved as a separate file with its name containing the TLE data.

------------------------------------------------------------------------------------------------------------------
