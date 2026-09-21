import axios from 'axios'

const server = axios.create({
    baseURL: '/api',
    timeout: 5000
})

server.interceptors.request.use(config => {
  const token = localStorage.getItem('token')
  if (token) config.headers.Authorization = `Bearer ${token}`
  return config
})

server.interceptors.response.use(
  
  response => {
    return response.data
  },
 
  error => {
    return Promise.reject(error)
  }
)
export default server
