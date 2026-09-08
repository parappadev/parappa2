#!/usr/bin/env python3

import subprocess
import json
import re
import os

import mapfile_parser

def save(data, filename):
    directory = os.path.dirname(filename)
    if not os.path.exists(directory):
        os.makedirs(directory)
    with open(filename, "w") as outfile:
        json.dump(data, outfile)

def getColor(percentage):
    if percentage >= 100:
        return "lime"
    elif percentage >= 75:
        return "green"
    elif percentage >= 50:
        return "yellow"
    if percentage >= 25:
        return "darkorange"
    else:
        return "crimson"

def parse_progress(output):
    lines = output.strip().split("\n")
    all_of_folder_percent = 0
    sdk_of_total_percent = 0
    folder_percentages = {}

    for line in lines[1:]: # Skip the header
        parts = re.split(r'\s{2,}', line.strip()) # Split by 2 or more spaces
        if len(parts) >= 5:
            category = parts[0]
            try:
                of_folder_percent = float(parts[4].strip('%'))
                folder_percentages[category] = of_folder_percent

                if category == "all":
                    all_of_folder_percent = of_folder_percent
                elif category == "sdk":
                    sdk_of_total_percent = float(parts[7].strip('()%'))
            except ValueError:
                print(f"Error on line: {line}")

    total_percentage = all_of_folder_percent + sdk_of_total_percent
    return total_percentage, folder_percentages

def main():
    command = ["python3", "-m", "mapfile_parser", "progress", "build/WAVE2PS2.IRX.map", "asm/iop_mdl/wp2cd/", "asm/iop_mdl/wp2cd/nonmatchings/", "-i 4", "-f"]
    result = subprocess.run(command, stdout=subprocess.PIPE, text=True)
    total_percentage, folder_percentages = parse_progress(result.stdout)

    print(f"Total percentage: {total_percentage:.4f}%")
    total_report = {
        "schemaVersion": 1,
        "label": f"Total percentage",
        "message": f"{total_percentage:.4f}%",
        "color": getColor(float(total_percentage)),
    }
    save(total_report, "progress/wp2cd.total_progress.json")
    
    #for category, percent in folder_percentages.items():
    #    if category not in ["sdk", "all"]: # Skip the sdk and all categories
    #        print(f"{category} percentage: {percent:.4f}%")
    #        report = {
    #            "schemaVersion": 1,
    #            "label": f"{category}",
    #            "message": f"{percent:.4f}%",
    #            "color": getColor(float(percent)),
    #        }

    #        save(report, f"progress/{category}_progress.json")

if __name__ == "__main__":
    main()
