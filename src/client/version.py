from platform import python_version as pv
from platform import python_version_tuple as pvt

def python_version_check():
    def python_version_fail():
        print("This computer does not meet the minimum requirement")
        print("Minimum requirement: python 3.4")
        print("Current version: python", platform.pv())
        exit()
    python_version = pvt()
    if int(python_version[0]) < 3:
        python_version_fail()
    elif int(python_version[0]) == 3:
        if int(python_version[1]) < 4:
            python_version_fail()

def product_version():
    product_name="Trainer"
    product_version="3.0"
    print(product_name, product_version)
    print()
