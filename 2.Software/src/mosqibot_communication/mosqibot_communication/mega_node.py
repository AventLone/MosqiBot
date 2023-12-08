import serial
import struct
import rclpy
from time import sleep
from rclpy.node import Node
from mosqibot_srv_interface.srv import MegaMsg


# Convert a list to bytes containing a uint8 and 2 float32
def to_bytesMessage(command: int, point) -> bytes:
    bytesMessage = bytearray()
    bytesMessage.append(command)
    for i in point:
        bytesMessage.extend(struct.pack("f", i))
    return bytes(bytesMessage)  # return a bytes object


class MegaServer(Node):
    def __init__(self, name):
        super().__init__(name)
        self.serial_ = None
        self.get_logger().info("Node has been activated: %s." % name)
        self.server = self.create_service(MegaMsg, "mega_server", self.callback)

    # destructor
    def __del__(self):
        if self.serial_ is not None:
            if self.serial_.is_open:
                self.serial_.close()
        self.get_logger().info("Node is shutdown.")

    # Send command to MCU for controlling the steppers and other motors
    def callback(self, request, response):
        self.get_logger().info("Device control request received.")
        self.serial_.write(to_bytesMessage(request.command, request.point_xy))

        message_read = self.serial_.readline()
        if message_read == b"Task done\r\n":
            response.flag = True
            self.get_logger().info("Task done.")
        else:
            response.flag = False
            self.get_logger().error("Task failed!")

        return response


def main(args=None):
    rclpy.init(args=args)

    node = MegaServer("mega")

    try:
        # node.serial_ = serial.Serial('/dev/ttyACM0', 115200)  # 设置端口
        node.serial_ = serial.Serial("/dev/ttyUSB0", 115200)  # 设置端口
    except:
        node.get_logger().error("Open serial failed!")
        import sys
        sys.exit(1)
    sleep(1)

    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
