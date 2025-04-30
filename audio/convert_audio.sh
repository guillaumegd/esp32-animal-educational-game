mkdir -p converted && for f in orig/*.mp3; do ffmpeg -i "$f" -acodec libmp3lame -ab 128k -ar 44100 -ac 1 "converted/$(basename "$f")"; done
