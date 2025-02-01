# Set your project directory
PROJECT_DIR="$HOME/Documents/arduino/libraries/EEPROM-Storage/examples/General/tests"

# Set the target device platform (e.g., argon, photon, boron)
PLATFORM="argon"

# Navigate to the project directory
cd "$PROJECT_DIR" || { echo "Project directory not found"; exit 1; }

# Compile the firmware
particle compile $PLATFORM . --saveTo firmware.bin

# Check if the compilation was successful
if [ $? -eq 0 ]; then
{
    echo "Compilation successful! Firmware saved as firmware.bin"
    echo "Entering DFU mode."
    particle usb dfu
    echo "Flashing firmware."
    particle flash --usb firmware.bin
    echo "Removing firmware file."
    rm firmware.bin
    echo "Starting serial port monitor in 10 seconds..."
    sleep 10
    particle serial monitor --follow
}
else
    echo "Compilation failed. Check for errors."
fi