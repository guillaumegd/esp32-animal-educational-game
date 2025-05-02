find orig -type f -name "*.mp3" | while read -r f; do
  out="converted/${f#orig/}"                        # extrait le chemin relatif
  mkdir -p "$(dirname "$out")"                      # crée les dossiers nécessaires
  ffmpeg -i "$f" -acodec libmp3lame -ab 128k -ar 44100 -ac 1 "$out"
done