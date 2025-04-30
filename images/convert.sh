mkdir -p converted && for f in original/*; do
  magick "$f" -resize 160x128^ -gravity center -extent 160x128 -define bmp:format=bmp3 "converted/$(basename "${f%.*}").bmp"
done