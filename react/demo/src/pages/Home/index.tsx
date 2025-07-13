import { useLoaderData, useSubmit, NavLink } from "react-router";
import { Form, Input, Button } from "antd";
export default function Home() {
  const { data } = useLoaderData();
  const submit = useSubmit();
  // onFinish -> action -> api
  const onFinish = (values: any) => {
    submit(values, {
      method: "post",
      encType: "application/json", // 默认formData
    });
  };
  return (
    <>
      <Form onFinish={onFinish}>
        <Form.Item label="页面" name="name">
          <Input />
        </Form.Item>
        <Form.Item label="路径" name="path">
          <Input />
        </Form.Item>
        <Form.Item>
          <Button type="primary" htmlType="submit">
            提交
          </Button>
        </Form.Item>
      </Form>

      {data.map((item) => (
        <div>
          <NavLink to={item.path} key={item.path}>
            {item.name}
          </NavLink>
        </div>
      ))}
    </>
  );
}
