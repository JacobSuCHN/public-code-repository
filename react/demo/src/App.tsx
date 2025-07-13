import React, { useEffect, useState } from "react";
import usePointStore from "./store/point";
import { useShallow } from "zustand/shallow";
const App: React.FC = () => {
  const { point, incrementPoint } = usePointStore(
    useShallow((state) => ({
      point: state.point,
      incrementPoint: state.incrementPoint,
    }))
  );
  const [pointStatus, setPointStatus] = useState("");
  useEffect(() => {
    usePointStore.subscribe(
      (state) => state.point,
      (point) => {
        console.log("🚀 ~ useEffect ~ point:", point)
        if (point >= 26) {
          setPointStatus("合格");
        } else {
          setPointStatus("不合格");
        }
      },
      {
        fireImmediately: true,
      }
    );
  },[]);
  return (
    <>
      <div>{point}</div>
      <div>{pointStatus}</div>
      <button onClick={incrementPoint}>+1</button>
    </>
  );
};

export default App;
