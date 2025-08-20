import { defineStore } from 'pinia'
import * as PIXI from 'pixi.js'
import { Live2DModel } from 'pixi-live2d-display'

// Extend the Window interface to include PIXI
declare global {
  interface Window {
    PIXI: typeof PIXI
  }
}

window.PIXI = PIXI
interface Live2DState {
  model: PIXI.DisplayObject & Live2DModel | null
  mouthInterval: number | null
}

export const useLive2DStore = defineStore('live2d', {
  state: (): Live2DState => ({
    model: null,
    mouthInterval: null
  }),

  actions: {
    async initializeModel(canvas: HTMLCanvasElement) {
      if (!canvas || this.model) return

      const app = new PIXI.Application({
        view: canvas,
        transparent: true,
        autoStart: true,
        resolution: window.devicePixelRatio || 1,
        resizeTo: canvas,
      })

      this.model = await Live2DModel.from('/live2d/kei_basic_free.model3.json')
      this.model.scale.set(0.5)
      this.model.position.set(0, 0)
      this.model.autoInteract = false
      this.model.interactive = false
      app.stage.addChild(this.model as unknown as PIXI.DisplayObject)
    },

    startSpeak() {
      if (!this.model) return

      this.stopSpeak()  // 避免重复启动

      this.mouthInterval = setInterval(() => {
        const n = Math.random();
        (this.model?.internalModel.coreModel as { setParameterValueById: (id: string, value: number) => void }).setParameterValueById('ParamMouthOpenY', n);
      }, 100)
    },

    stopSpeak() {
      if (this.mouthInterval) {
        clearInterval(this.mouthInterval)
        this.mouthInterval = null
      }

      // 可选：重置嘴巴状态
      if (this.model) {
        (this.model.internalModel.coreModel as { setParameterValueById: (id: string, value: number) => void }).setParameterValueById('ParamMouthOpenY', 0)
      }
    }
  }
})
