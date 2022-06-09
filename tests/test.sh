reset="\e[0m"
green="\e[92m"
red="\e[91m"

for file in debug/*; do
    if ./"$file" > /dev/null ; then
        echo "$green""$file" "OK" "$reset"
    else
        echo "$red""$file" "FAIl" "$reset"
    fi
done;