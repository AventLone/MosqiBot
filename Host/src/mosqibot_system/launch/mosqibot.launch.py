import os
import launch
from launch.event_handlers import OnProcessExit
from launch.actions import RegisterEventHandler
# from launch import event_handler
from launch_ros.substitutions import FindPackageShare
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    mosqibot_system_dir = FindPackageShare(package="mosqibot_system").find("mosqibot_system")
    camera_settings_file = os.path.join(mosqibot_system_dir, "config/param/v4l2_camera.yaml")

    # define the camera node
    node_camera = Node(
        package="v4l2_camera", executable="v4l2_camera_node", emulate_tty=True,
        arguments=['--ros-args', '--log-level', 'warn'],
        parameters=[camera_settings_file]
    )
    node_mosqibot_communication = Node(
        package="mosqibot_communication", executable="mega_node",
        emulate_tty=True, output="screen"
    )
    node_mosqibot_system = Node(
        package="mosqibot_system", executable="mosqibot_system",
        emulate_tty=True, output="screen",
        parameters=[{'MosquitoTargetNum': 3}]
    )
    node_qtUi = Node(package="mosqibot_ui_test", executable="MosqiBot")

    # This will make the whole launch processes exit after "node_qtUi" exit.
    event = RegisterEventHandler(
        event_handler=OnProcessExit(
            target_action=node_qtUi,
            on_exit=[launch.actions.EmitEvent(event=launch.events.Shutdown())]
        )
    )

    # Action about time delay
    node_mosqibot_system_delay = launch.actions.TimerAction(
        period=1.0,  # the unit is second
        actions=[node_mosqibot_system]
    )

    ld = LaunchDescription()
    ld.add_action(event)
    ld.add_action(node_qtUi)
    ld.add_action(node_mosqibot_communication)
    ld.add_action(node_camera)
    ld.add_action(node_mosqibot_system_delay)

    return ld
