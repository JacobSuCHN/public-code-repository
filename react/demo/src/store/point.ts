import { create } from 'zustand'
import { immer } from 'zustand/middleware/immer'
import { subscribeWithSelector } from 'zustand/middleware'
interface PointStore {
  point: number,
  incrementPoint: () => void
}
const usePointStore = create<PointStore>(
  immer(
    subscribeWithSelector(
      (set) => ({
        point: 55,
        incrementPoint: () => set((state) => {
          state.point = state.point + 1
        })
      })
    )
  )
)

export default usePointStore