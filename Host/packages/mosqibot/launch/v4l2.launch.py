import os

# from ament_index_python.packages import get_package_share_directory
from launch_ros.substitutions import FindPackageShare
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    camera_client_dir = FindPackageShare(package="camera_client").find("camera_client")
    camera_settings_file = os.path.join(camera_client_dir, "param/camera_setting.yaml")
    # camera_settings_file = os.path.join(parameter_dir, "camera_setting.yaml")

    # define the camera node
    camera_node = Node(package="v4l2_camera", executable="v4l2_camera_node", parameters=[camera_settings_file])
    image_view_node = Node(package="rqt_image_view", executable="rqt_image_view")
    # image_view_node = Node(
    #     package="camera_client", executable="undistort_node", output="screen"
    # )

    # create the launch description
    ld = LaunchDescription()
    ld.add_action(camera_node)
    ld.add_action(image_view_node)

    return ld
