import { create } from "zustand"
import { createJSONStorage, persist } from "zustand/middleware";
import { immer } from 'zustand/middleware/immer'
interface User {
  gourd: {
    gourd1: string,
    gourd2: string,
    gourd3: string,
    gourd4: string,
    gourd5: string,
    gourd6: string,
    gourd7: string,
  },
  updateGourd: () => void
}
const logger = (config) => (set, get, api) =>
  config(
    (...args) => {
      console.log(api);
      console.log("before", get());
      set(...args);
      console.log("after", get());
    },
    get,
    api
  );
const useUserStore = create<User>()(
  immer(
    persist(
      (set) => ({
        gourd: {
          gourd1: "gourd1",
          gourd2: "gourd2",
          gourd3: "gourd3",
          gourd4: "gourd4",
          gourd5: "gourd5",
          gourd6: "gourd6",
          gourd7: "gourd7",
        },
        updateGourd: () =>
          set(state => { state.gourd.gourd1 = state.gourd.gourd1 + "plus" }),
      }),
      {
        name: "user", // 仓库名称(唯一)
        storage: createJSONStorage(() => localStorage), // 存储方式 可选 localStorage sessionStorage IndexedDB 默认localStorage
        partialize: (state) => ({
          name: state.gourd.gourd1,
          age: state.gourd.gourd2,
        }), // 部分状态持久化
      }
    )
  )
)
export default useUserStore