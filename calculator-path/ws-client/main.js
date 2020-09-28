
document.addEventListener("DOMContentLoaded", ()=>{
  const ws = new WebSocket('ws://localhost:8080')
  document.getElementById('loader').onclick=()=>{document.getElementById('loaded').click()}
  document.getElementById('loaded').addEventListener('change', (event)=>{
    const reader = new FileReader()
    reader.onload = ()=>{
      document.getElementById('in').innerHTML=reader.result
      ws.send(reader.result)
    }
    reader.readAsText(event.target.files[event.target.files.length-1])
  })
  ws.addEventListener('open', () => {
    document.getElementById('status').innerHTML='OPEN'
  })
  ws.addEventListener('message', function (event) {
    document.getElementById('out').innerHTML+=JSON.stringify(JSON.parse(event.data), undefined, 1)+'\n\n\n'
    console.log(event.data)
  })
  ws.addEventListener('close', (event) => {
    document.getElementById('status').innerHTML='CLOSED'
  })
  ws.addEventListener('error', (error) => {
    document.getElementById('status').innerHTML='ERROR'
    console.error(error)
    ws.close()
  })
})
