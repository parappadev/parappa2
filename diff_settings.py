def apply(config, args):
    if args.target == "ee":
        config["arch"] = "mipsee"
        config["baseimg"] = f"iso/SCPS_150.17.rom"
        config["myimg"] = f"build/SCPS_150.17.rom"
        config["mapfile"] = f"build/SCPS_150.17.map"
    elif args.target == "wp2cd":
        config["arch"] = "mipsel"
        config["baseimg"] = f"iso/WAVE2PS2.IRX.rom"
        config["myimg"] = f"build/WAVE2PS2.IRX.rom"
        config["mapfile"] = f"build/WAVE2PS2.IRX.map"
    elif args.target == "tapctrl":
        # Nothing for now.
        config["arch"] = "mipsel"
        config["baseimg"] = f"NONE"
        config["myimg"] = f"NONE"
        config["mapfile"] = f"NONE"

    config["source_directories"] = [
        "src",
        "asm",
        "include",
        "assets",
    ]
    config["make_command"] = ["ninja"]
    config["expected_dir"] = f"expected/"