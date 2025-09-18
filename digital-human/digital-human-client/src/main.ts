import { createApp } from 'vue'
import { createPinia } from 'pinia'

import '@/assets/css/index.css'

import App from './App.vue'
import router from './router'

import { showAlert } from './utils/useAlert'


const app = createApp(App)

app.config.globalProperties.$showAlert = showAlert


app.use(createPinia())
app.use(router)

app.mount('#app')
