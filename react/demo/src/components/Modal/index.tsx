import './index.css';
const Modal = () => {
  return <div className="modal">
    <div className="modal-header">
      <div className="modal-title">Title</div>
    </div>
    <div className="modal-content">
      <h1>Modal</h1>
    </div>
    <div className="modal-footer">
      <button className="modal-close-button">Close</button>
      <button className="modal-confirm-button">Confirm</button>
    </div>
  </div>
}
export default Modal;