#!/bin/bash

FILE="addressbook.txt"

while true
do
    echo ""
    echo "----- ADDRESS BOOK -----"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"

    read -p "Enter your choice: " ch

    case $ch in

    1)
        > "$FILE"
        echo "Address Book Created Successfully!"
        ;;

    2)
        if [ -f "$FILE" ]; then
            echo "----- Address Book Records -----"
            if [ -s "$FILE" ]; then
                cat "$FILE"
            else
                echo "Address Book is Empty."
            fi
        else
            echo "Address Book does not exist."
        fi
        ;;

    3)
        read -p "Enter ID: " id
        read -p "Enter Name: " name
        read -p "Enter Phone: " phone
        read -p "Enter Address: " address

        echo "$id|$name|$phone|$address" >> "$FILE"
        echo "Record Inserted Successfully!"
        ;;

    4)
        read -p "Enter ID to Delete: " id

        if grep -q "^$id|" "$FILE"; then
            grep -v "^$id|" "$FILE" > temp.txt
            mv temp.txt "$FILE"
            echo "Record Deleted Successfully!"
        else
            echo "Record Not Found!"
        fi
        ;;

    5)
        read -p "Enter ID to Modify: " id

        if grep -q "^$id|" "$FILE"; then
            grep -v "^$id|" "$FILE" > temp.txt

            read -p "Enter New Name: " name
            read -p "Enter New Phone: " phone
            read -p "Enter New Address: " address

            echo "$id|$name|$phone|$address" >> temp.txt
            mv temp.txt "$FILE"

            echo "Record Modified Successfully!"
        else
            echo "Record Not Found!"
        fi
        ;;

    6)
        echo "Exiting Address Book..."
        exit
        ;;

    *)
        echo "Invalid Choice!"
        ;;

    esac
done


chmod +x addressbook.sh
./addressbook.sh