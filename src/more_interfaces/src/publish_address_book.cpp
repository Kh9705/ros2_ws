#include <chrono>
#include <memory>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using namespace std::chrono_literals;

class AddressBookPublisher : public rclcpp::Node
{
public:
  AddressBookPublisher()
  : Node("address_book_publisher")
  {
    address_book_publisher_ =
      this->create_publisher<more_interfaces::msg::AddressBook>(
        "address_book", 10);

    auto publish_msg = [this]() {
      more_interfaces::msg::AddressBook message;

      message.first_name = "Khushhal";
      message.last_name = "Sinha";
      message.phone_number = "1234567899";
      message.phone_type =
        more_interfaces::msg::AddressBook::PHONE_TYPE_MOBILE;

      RCLCPP_INFO(
        this->get_logger(),
        "Publishing Contact: %s %s",
        message.first_name.c_str(),
        message.last_name.c_str()
      );

      this->address_book_publisher_->publish(message);
    };

    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private:
  rclcpp::Publisher<more_interfaces::msg::AddressBook>::SharedPtr
    address_book_publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<AddressBookPublisher>());
  rclcpp::shutdown();
  return 0;
}
