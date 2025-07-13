import { useSyncExternalStore } from "react"
// history api去实现 跳转页面 监听history变化
export const useHistory = () => {
  const subscribe = (callback: () => void) => {
    window.addEventListener("popstate", callback)
    window.addEventListener("hashchange", callback)
    return () => {
      window.removeEventListener("popstate", callback)
      window.removeEventListener("hashchange", callback)
    }
    // popstate: 只能监听浏览器的前进后退
  }
  const getSnapshot = () => {
    return window.location.href
  }
  const url = useSyncExternalStore(subscribe, getSnapshot)
  const push = (path: string) => {
    window.history.pushState(null, "", path)
    window.dispatchEvent(new PopStateEvent("popstate"))
  }
  const replace = (path: string) => {
    window.history.replaceState(null, "", path)
    window.dispatchEvent(new PopStateEvent("popstate"))
  }
  return [url, push, replace] as const // 返回一个元组
}