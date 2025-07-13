import { Menu as AntdMenu } from "antd";
import { AppstoreOutlined } from "@ant-design/icons";
import type { MenuProps } from "antd";
import { useNavigate } from "react-router";
export default function Menu() {
  const navigate = useNavigate(); // 编程式导航
  const handleClick: MenuProps["onClick"] = (info) => {
    navigate(info.key);
  };
  const menuItems = [
    {
      key: "/home",
      label: "Home",
      icon: <AppstoreOutlined />,
    },
    {
      key: "/about",
      label: "About",
      icon: <AppstoreOutlined />,
    },
  ];
  return (
    <AntdMenu
      onClick={handleClick}
      style={{ height: "100vh" }}
      items={menuItems}
    />
  );
}
