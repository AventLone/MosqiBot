import os
import launch
from launch.event_handlers import OnProcessExit
from launch.actions import RegisterEventHandler
# from launch import event_handler
from launch_ros.substitutions import FindPackageShare
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    camera_client_dir = FindPackageShare(
        package="camera_client").find("camera_client")
    camera_settings_file = os.path.join(
        camera_client_dir, "param/camera_setting.yaml")

    # define the camera node
    node_camera = Node(
        package="v4l2_camera",
        executable="v4l2_camera_node",
        parameters=[camera_settings_file]
    )
    node_arduino = Node(package="arduino_pkg", executable="mega_node", output="screen")
    node_client = Node(package="camera_client", executable="camera_client", output="screen")
    node_qtUi = Node(package="qt_ui_test", executable="MosqiBot_test")
    event = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=node_qtUi,
            on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())]
        )
    )

    ld = LaunchDescription()
    ld.add_action(node_qtUi)
    ld.add_action(node_arduino)
    ld.add_action(node_camera)
    ld.add_action(node_client)
    ld.add_action(event)

    return ld
