// src/stores/useAlertStore.ts
import { defineStore } from 'pinia'
import { ref, computed } from 'vue'
import Alert from '@/components/AlertModal.vue'
import { createApp, h, type App, type ComponentPublicInstance } from 'vue'

type AlertType = 'success' | 'error' | 'info' | 'warning'

interface AlertOptions {
  message: string
  type?: AlertType
  duration?: number
}

interface AlertInstance {
  id: number
  message: string
  type: AlertType
  duration: number
  offsetIndex: number
  app: App<Element> | null
  container: HTMLDivElement | null
  componentInstance: ComponentPublicInstance | null
}

const MAX_ALERTS = 10
const VERTICAL_OFFSET = 3 // vw

export const useAlertStore = defineStore('alert', () => {
  const alerts = ref<AlertInstance[]>([])
  const alertId = ref(0)

  const alertCount = computed(() => alerts.value.length)

  function calculatePosition(index: number): string {
    return `${1 + index * VERTICAL_OFFSET}vw`
  }

  function repositionAlerts() {
    alerts.value.forEach((alert, index) => {
      const newOffset = calculatePosition(index)
      const component = alert.componentInstance as ComponentPublicInstance

      if (component.$props) {
        const props = component.$props as { offset?: string }
        props.offset = newOffset
      }

      alert.offsetIndex = index
    })
    console.log("🚀 ~ repositionAlerts ~ alerts:", alerts)
  }

  function removeAlert(id: number) {
    const index = alerts.value.findIndex(alert => alert.id === id)
    if (index !== -1) {
      const alert = alerts.value[index]
      if (alert.app && alert.container) {
        alert.app.unmount()
        document.body.removeChild(alert.container)
      }
      alerts.value.splice(index, 1)
      repositionAlerts()
    }
  }

  function showAlert({ message, type = 'info', duration = 3000 }: AlertOptions) {
    if (alertCount.value >= MAX_ALERTS) {
      const oldest = alerts.value[0]
      removeAlert(oldest.id)
    }

    const id = alertId.value++
    const offsetIndex = alertCount.value

    const container = document.createElement('div')
    document.body.appendChild(container)

    const app = createApp({
      render() {
        return h(Alert, {
          message,
          type,
          duration,
          offset: calculatePosition(offsetIndex),
          onClose: () => {
            removeAlert(id)
          },
        })
      },
    })

    const instance = app.mount(container) as ComponentPublicInstance

    alerts.value.push({
      id,
      message,
      type,
      duration,
      offsetIndex,
      app,
      container,
      componentInstance: instance,
    })

    repositionAlerts()
  }

  return {
    alerts,
    alertCount,
    showAlert,
    removeAlert,
  }
})
