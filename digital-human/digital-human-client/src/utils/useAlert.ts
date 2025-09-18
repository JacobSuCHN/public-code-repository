import { createApp, h, ref, type Ref } from 'vue'
import Alert from '@/components/AlertModal.vue'

type AlertType = 'success' | 'error' | 'info' | 'warning'
const MAX_ALERTS = 15
const VERTICAL_OFFSET = 6

interface AlertInstance {
  message: string
  type: AlertType
  duration: number
  verticalOffset: Ref<string> // 改为 Ref 类型
  container: HTMLDivElement
  app: ReturnType<typeof createApp>
}

const alertQueue: AlertInstance[] = []
const activeAlertsList: AlertInstance[] = []

function calculatePosition(index: number): string {
  return `${4 + index * VERTICAL_OFFSET}vh`
}

function repositionAlerts() {
  activeAlertsList.forEach((alert, index) => {
    const newOffset = calculatePosition(index)
    // 直接更新响应式变量值
    alert.verticalOffset.value = newOffset
  })
}

export function showAlert(
  message: string,
  type: AlertType = 'info',
  duration: number = 3000
) {
  // 队列满时移除最早提示
  if (alertQueue.length >= MAX_ALERTS) {
    const oldest = alertQueue.shift()!
    oldest.app.unmount()
    document.body.removeChild(oldest.container)
    const indexInActive = activeAlertsList.indexOf(oldest)
    if (indexInActive !== -1) {
      activeAlertsList.splice(indexInActive, 1)
    }
    repositionAlerts() // 立即重新布局
  }

  const container = document.createElement('div')
  document.body.appendChild(container)

  const initialOffset = calculatePosition(activeAlertsList.length)
  const verticalOffsetRef = ref(initialOffset) // 创建响应式偏移量

  const newAlert: AlertInstance = {
    message,
    type,
    duration,
    verticalOffset: verticalOffsetRef, // 存储响应式引用
    container,
    app: createApp({
      render() {
        return h(Alert, {
          message,
          type,
          duration,
          offset: verticalOffsetRef.value,  // 传递当前值
          onClose: () => {
            // 清理逻辑
            const index = activeAlertsList.findIndex(a => a === newAlert)
            if (index !== -1) activeAlertsList.splice(index, 1)

            const queueIndex = alertQueue.findIndex(a => a === newAlert)
            if (queueIndex !== -1) alertQueue.splice(queueIndex, 1)

            newAlert.app.unmount()
            document.body.removeChild(newAlert.container)
            repositionAlerts() // 关闭后重新布局
          }
        })
      }
    })
  }

  newAlert.app.mount(container)
  alertQueue.push(newAlert)
  activeAlertsList.push(newAlert)
}
