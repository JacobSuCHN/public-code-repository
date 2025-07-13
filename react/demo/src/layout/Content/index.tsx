import { Outlet, useNavigation } from "react-router";
import { Alert, Spin } from "antd";
export default function Content() {
  const navigation = useNavigation();
  console.log(navigation.state);
  const isLoading = navigation.state === "loading";
  return (
    <div>
      {isLoading ? (
        <Spin size="large" tip="loading...">
          <Alert
            description="正在加载中，请稍等"
            message="加载中"
            type="info"
          />
        </Spin>
      ) : (
        <Outlet />
      )}
    </div>
  );
}
