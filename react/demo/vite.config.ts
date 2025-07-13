import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react-swc'
// vite 插件
import type { Plugin } from 'vite'
import mockjs from 'mockjs'
import url from 'node:url'
const viteMockServer = (): Plugin => {
  return {
    name: 'vite:mock-server',
    configureServer(server) {
      server.middlewares.use('/api/list', (req, res) => {
        const parseUrl = url.parse(req.originalUrl!, true).query
        res.setHeader("Content-Type", "application/json;charset=utf-8")
        const data = mockjs.mock({
          'list|1000': [
            {
              'id|+1': 1,
              'name': `@name(true)`,
              'keyword': parseUrl.name,
              'age|18-60': 1,
              'gender|1': ['Male', 'Female']
            }
          ]
        })
        res.end(JSON.stringify(data))
      })
    }
  }
}
// https://vite.dev/config/
export default defineConfig({
  css: {
    modules: {
      localsConvention: 'dashes', // 修改css modules的类名规则 可以改成驼峰命名 或者 xxx-xxx命名等
      generateScopedName: '[name]__[local]___[hash:base64:5]', // 修改css modules的类名规则 name:组件名 local:css属性名 hash:base64:5
    }
  },
  plugins: [react(), viteMockServer()],
})
