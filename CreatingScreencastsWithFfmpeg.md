# Creating screencasts using ffmpeg #

While experimenting with creating demo videos for QBoard, i had to tinker
quite a lot to get the video capture working how i wanted it. For anyone
doing screencasts (whether of QBoard or not), here's a simple shell script
which can simplify the process:

```
#!/bin/bash
# Generates an ffmpeg command line for capturing a given X11 window.
# Usage: $0 [optional output file name]
# It will prompt you to click on the window you want to capture.
# Output is simply echoed, for use in copy/pasting (adjusting/adding
# parameters as needed).
# Tip: the command uses screen coordinates, so do not resize or move
# the target window once capturing as begun.
echo "Click the window to capture..."

tmpfile=/tmp/screengrab.tmp.$$
trap 'touch $tmpfile; rm -f $tmpfile' 0

xwininfo > $tmpfile 2>/dev/null
left=$(grep 'Absolute upper-left X:' $tmpfile | awk '{print $4}');
top=$(grep 'Absolute upper-left Y:' $tmpfile | awk '{print $4}');
width=$(grep 'Width:' $tmpfile | awk '{print $2}');
height=$(grep 'Height:' $tmpfile | awk '{print $2}');
geom="-geometry ${width}x${height}+${left}+${top}"
echo "Geometry: ${geom}"
size="${width}x${height}"
pos="${left},${top}"
echo "pos=$pos size=$size"

out=${1-screengrab.avi}
#test -f $out && rm $out

framerate=4
echo "# ffmpeg command"
echo -n "sleep 2; " # give caller time to switch to captured window
echo ffmpeg -f x11grab \
    -r ${framerate} \
    -s ${size} \
    -i ${DISPLAY-0:0}+${pos} \
    -sameq \
    $out
```


It's used like this:

```
stephan@jareth:/space/stephan$ ./screencap.sh
Click the window to capture...
Geometry:   -geometry 598x686+764+0
pos=764,0 size=598x686
# ffmpeg command
sleep 2; ffmpeg -f x11grab -r 4 -s 598x686 -i :0.0+764,0 -sameq screengrab.avi
```

The output is intended to be copy/pasted to your shell (or script, or whatever), adding or adjusting parameters as necessary. The `sleep` call is helpful when running the command from a shell, as it gives the caller time to click on the target window before ffmpeg starts capturing.