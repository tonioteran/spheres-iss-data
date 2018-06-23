#/bin/bash

# Script to turn a video into a GIF:
# Parameters:
# 1 = path to video file
# 2 = height of gif
# 3 = fps
# 4 = delay between frames
# 5 = amount of fuzz

# Create frames from the video
mkdir -p frames
ffmpeg -i $1 -vf scale=$2:-1:flags=lanczos,fps=$3 frames/ffout%04d.png

# Print out total number of created frames:
echo "Total number of frames = `find frames/ -type f | wc -l`"

# Convert frames to GIF:
convert -delay $4 -loop 0 -dither None -colors 80 "frames/ffout*.png" -fuzz $5 -layers OptimizeFrame "${1}.gif"

# Delete the frames:
rm -rf frames



