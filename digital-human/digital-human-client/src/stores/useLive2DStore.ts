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
  app: PIXI.Application | null
}

export const useLive2DStore = defineStore('live2d', {
  state: (): Live2DState => ({
    model: null,
    mouthInterval: null,
    app: null
  }),

  actions: {
    async initializeModel(canvas: HTMLCanvasElement) {
      if (!canvas) return

      const RENDER_WIDTH = 4096
      const RENDER_HEIGHT = 4096

      this.app = new PIXI.Application({
        view: canvas,
        transparent: true,
        autoStart: true,
        resolution: 1, // 固定分辨率为 1
        width: RENDER_WIDTH,
        height: RENDER_HEIGHT,
        // 移除 resizeTo
      })

      // 设置 canvas 的 CSS 显示尺寸为视窗宽度的 30%
      canvas.style.width = '30vw'
      canvas.style.height = '30vw'

      // 设置像素尺寸固定为 RENDER_WIDTH x RENDER_HEIGHT
      canvas.width = RENDER_WIDTH
      canvas.height = RENDER_HEIGHT

      this.model = await Live2DModel.from('/live2d/kei_basic_free.model3.json')

      // 让模型适配固定像素尺寸
      const scale = RENDER_WIDTH / this.model.width
      this.model.scale.set(scale)
      this.model.position.set(RENDER_WIDTH / 2, RENDER_HEIGHT / 2)
      this.model.anchor?.set(0.5, 0.5)
      this.model.autoInteract = false
      this.model.interactive = false

      this.app.stage.addChild(this.model as unknown as PIXI.DisplayObject)

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
    },
  }
})
