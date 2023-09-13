from setuptools import setup

package_name = "arduino_pkg"

setup(
    name=package_name,
    version="0.0.0",
    packages=[package_name],
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="avent",
    maintainer_email="piggystoic@outlook.com",
    description="TODO: Package description",
    license="TODO: License declaration",
    tests_require=["pytest"],
    entry_points={
        "console_scripts": [
            "mega_node = arduino_pkg.mega_node:main",
            "uno_node = arduino_pkg.uno_node:main"
        ]
    },
)
