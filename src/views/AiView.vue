<template>
  <div class="container">
    <!-- 顶部操作栏 -->
    <div class="toolbar">
      <div class="toolbar-left">
        <el-button type="primary" plain @click="newChat">
          <el-icon><Plus /></el-icon>
          新对话
        </el-button>
      </div>
      <div class="toolbar-right">
        <el-button text @click="openHistory">
          <el-icon><Clock /></el-icon>
          历史记录
        </el-button>
      </div>
    </div>

    <!-- 标题 -->
    <div class="title">
      <h1>AI 问答</h1>
      <p class="subtitle">登录后即可与 AI 对话</p>
    </div>

    <!-- 对话区 -->
    <div class="answer">
      <div
        v-for="(item, index) in messages"
        :key="index"
        :class="['message', item.role]"
      >
        <div class="avatar">{{ item.role === 'user' ? '我' : 'AI' }}</div>
        <div class="bubble">{{ item.content }}</div>
      </div>

      <div v-if="messages.length === 0" class="empty">
        输入你的问题，开始对话吧
      </div>
    </div>

    <!-- 表单 -->
    <div class="form">
      <el-form :model="form" ref="formRef" :rules="rules">
        <el-form-item prop="question">
          <el-input
            v-model="form.question"
            size="large"
            placeholder="请输入问题，按 Enter 发送"
            type="textarea"
            :rows="3"
            auto-size
            @keyup.enter="submitForm"
          ></el-input>
        </el-form-item>
        <el-form-item>
          <el-button
            type="primary"
            size="large"
            :loading="loading"
            @click="submitForm"
            class="send-btn"
          >
            发送
          </el-button>
        </el-form-item>
      </el-form>
    </div>

    <!-- 遮罩 -->
    <div v-if="showHistory" class="mask" @click="closeHistory"></div>

    <!-- 历史侧边栏 -->
    <div :class="['history-panel', { show: showHistory }]">
      <div class="history-header">
        <span>历史对话</span>
        <el-icon class="close-icon" @click="closeHistory">
          <Close />
        </el-icon>
      </div>

      <ul class="history-list">
        <li
          v-for="(item, index) in historyList"
          :key="index"
          :class="['history-item', { active: item.active }]"
          @click="selectHistory(item)"
        >
          <el-icon><ChatDotRound /></el-icon>
          <span class="history-title">{{ item.title }}</span>
          <el-icon class="delete-icon" @click.stop="deleteHistory(index)">
            <Delete />
          </el-icon>
        </li>

        <li v-if="historyList.length === 0" class="history-empty">
          暂无历史记录
        </li>
      </ul>
    </div>
  </div>
</template>

<script setup>
import { ref } from 'vue'
import { ask } from '@/Api/index'
import { ElMessage } from 'element-plus'
import { Plus, Clock, Close, ChatDotRound, Delete } from '@element-plus/icons-vue'
import { saveChat, getChatList } from '@/Api/index'
import { onMounted } from 'vue'
import { deleteChat, getChat } from '@/Api/index'



const formRef = ref(null)
const loading = ref(false)

const rules = ref({
  question: [
    { required: true, message: '请输入问题', trigger: 'blur' }
  ]
})

const form = ref({
  question: '',
  token: localStorage.getItem('token')
})

const messages = ref([])

// ===== 历史记录 =====
const showHistory = ref(false)
const historyList = ref([
  { title: '今天和 AI 聊了 Java 问题', active: true },
  { title: '关于 Spring Security 的讨论', active: false },
  { title: '前端布局优化建议', active: false }
])

const openHistory = () => {
  showHistory.value = true
  getChatList().then(res => {
    if (res.code === 200) {
      historyList.value = res.data
    } else {
      ElMessage.error(res.msg)
    }
  }).catch(() => {
    ElMessage.error('获取历史对话失败，请稍后重试')
  })
 
}



const closeHistory = () => {
  showHistory.value = false
}

const selectHistory = (item) => {
  historyList.value.forEach(h => h.active = false)
  item.active = true
  currentChatId.value = item.id
  getChat(item.id).then(
    res => {
      if (res.code === 200) {
        messages.value = res.data
      } else {
        ElMessage.error(res.msg)
      }
    }).catch(() => {
      ElMessage.error('获取对话失败，请稍后重试')
    }
  )
  closeHistory()
}







const deleteHistory = (index) => {
  const item = historyList.value[index]
  deleteChat(item.id).then(res => {
    if (res.code === 200) {
      ElMessage.success('对话已删除')
    } else {
      ElMessage.error(res.msg)
    }
  }).catch(() => {
    ElMessage.error('删除对话失败，请稍后重试')
  }).finally(() => {
    historyList.value.splice(index, 1)
  })
}
const currentChatId = ref(null)
// 新对话
const newChatForm = ref({
  
  title: '新对话',
  messages: [],
  id: null
})
const newChat = () => {

  newChatForm.value.messages = [...messages.value]
  newChatForm.value.title = messages.value[0]?.content?.slice(0, 20) || '新对话'
  newChatForm.value.id = currentChatId.value
  saveChat(newChatForm.value).then(res => {

    if (res.code === 200) {
     
      ElMessage.success('新对话已创建')
    } else {
      ElMessage.error(res.msg)
    }
  }).catch(() => {
    ElMessage.error('新对话失败，请稍后重试')
  })

   messages.value = []
  historyList.value.forEach(h => h.active = false)
}

// ===== 发送问答 =====
const submitForm = () => {
  formRef.value.validate().then(() => {
    loading.value = true
    messages.value.push({ role: 'user', content: form.value.question })

    ask(form.value).then(res => {
      form.value.question = ''
      loading.value = false
      if (res.code === 200) {
        messages.value.push({ role: 'ai', content: res.data })
      } else {
        ElMessage.error(res.msg)
      }
    }).catch(() => {
      loading.value = false
      ElMessage.error('问答失败，请稍后重试')
    })
  }).catch(() => {
    ElMessage.error('请输入问题')
  })
}
onMounted(() => {
  getChatList().then(res => {
    if (res.code === 200) {
      historyList.value = res.data
    } else {
      ElMessage.error(res.msg)
    }
  }).catch(() => {
    ElMessage.error('获取历史对话失败，请稍后重试')
  })
})


</script>

<style scoped>
/* ===== 整体容器 ===== */
.container {
  display: flex;
  flex-direction: column;
  height: 100vh;
  padding: 24px;
  box-sizing: border-box;
  background: linear-gradient(135deg, #f0f2f5 0%, #e8f0fe 100%);
  font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", "PingFang SC",
    "Microsoft YaHei", sans-serif;
}

/* ===== 顶部操作栏 ===== */
.toolbar {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0 0 16px;
  flex-shrink: 0;
}

.toolbar-left,
.toolbar-right {
  display: flex;
  align-items: center;
}

/* ===== 标题 ===== */
.title {
  text-align: center;
  padding: 0 0 24px;
  flex-shrink: 0;
}

.title h1 {
  margin: 0;
  font-size: 26px;
  font-weight: 600;
  color: #1f2d3d;
  letter-spacing: 2px;
}

.subtitle {
  margin: 8px 0 0;
  font-size: 14px;
  color: #909399;
}

/* ===== 对话区 ===== */
.answer {
  flex: 1;
  min-height: 0;
  padding: 24px;
  overflow-y: auto;
  background-color: #ffffff;
  border-radius: 12px;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.06);
  margin-bottom: 20px;
  background-image: url('@/assets/ans.jpg');
  background-size: cover;
  background-position: center;
}

.empty {
  text-align: center;
  color: #c0c4cc;
  font-size: 14px;
  margin-top: 40px;
}

.message {
  display: flex;
  align-items: flex-start;
  margin-bottom: 20px;
  gap: 10px;
}

.message.user {
  flex-direction: row-reverse;
}

.avatar {
  flex-shrink: 0;
  width: 36px;
  height: 36px;
  border-radius: 50%;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 13px;
  font-weight: 600;
  color: #fff;
}

.message.user .avatar {
  background-color: #409eff;
}

.message.ai .avatar {
  background-color: #67c23a;
}

.bubble {
  max-width: 70%;
  padding: 12px 16px;
  border-radius: 12px;
  line-height: 1.7;
  word-break: break-word;
  white-space: pre-wrap;
  font-size: 14px;
}

.message.user .bubble {
  background-color: #409eff;
  color: #fff;
  border-top-right-radius: 2px;
}

.message.ai .bubble {
  background-color: #f4f4f5;
  color: #303133;
  border-top-left-radius: 2px;
}

/* ===== 表单区 ===== */
.form {
  flex-shrink: 0;
  background-color: #ffffff;
  padding: 16px 20px;
  border-radius: 12px;
  box-shadow: 0 2px 12px rgba(0, 0, 0, 0.06);
}

.send-btn {
  width: 100%;
}

/* ===== 遮罩 ===== */
.mask {
  position: fixed;
  inset: 0;
  background-color: rgba(0, 0, 0, 0.35);
  z-index: 999;
}

/* ===== 历史侧边栏 ===== */
.history-panel {
  position: fixed;
  top: 0;
  right: 0;
  width: 300px;
  height: 100vh;
  background-color: #ffffff;
  box-shadow: -2px 0 12px rgba(0, 0, 0, 0.08);
  display: flex;
  flex-direction: column;
  z-index: 1000;
  transform: translateX(100%);
  transition: transform 0.3s ease;
}

.history-panel.show {
  transform: translateX(0);
}

.history-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 16px 20px;
  font-size: 16px;
  font-weight: 600;
  color: #1f2d3d;
  border-bottom: 1px solid #ebeef5;
}

.close-icon {
  cursor: pointer;
  color: #909399;
  font-size: 18px;
  transition: color 0.2s;
}

.close-icon:hover {
  color: #409eff;
}

.history-list {
  flex: 1;
  overflow-y: auto;
  list-style: none;
  margin: 0;
  padding: 8px;
}

.history-item {
  display: flex;
  align-items: center;
  gap: 10px;
  padding: 12px 14px;
  border-radius: 8px;
  cursor: pointer;
  font-size: 14px;
  color: #303133;
  transition: background-color 0.2s;
  margin-bottom: 4px;
}

.history-item:hover {
  background-color: #f5f7fa;
}

.history-item.active {
  background-color: #ecf5ff;
  color: #409eff;
}

.history-title {
  flex: 1;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}

.delete-icon {
  color: #c0c4cc;
  font-size: 15px;
  opacity: 0;
  transition: opacity 0.2s, color 0.2s;
}

.history-item:hover .delete-icon {
  opacity: 1;
}

.delete-icon:hover {
  color: #f56c6c;
}

.history-empty {
  text-align: center;
  color: #c0c4cc;
  font-size: 14px;
  padding: 40px 0;
}

/* ===== 移动端 ===== */
@media (max-width: 768px) {
  .history-panel {
    width: 80%;
  }
}
</style>