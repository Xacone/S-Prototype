#include "MainWin.h"
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

Graphics_view_zoom::Graphics_view_zoom(QGraphicsView* view)
  : QObject(view), _view(view)
{
  _view->viewport()->installEventFilter(this);
  _view->setMouseTracking(true);
  _modifiers = Qt::ControlModifier;
  _zoom_factor_base = 1.0015;
}

void Graphics_view_zoom::gentle_zoom(double factor) {
  _view->scale(factor, factor);
  _view->centerOn(target_scene_pos);
  QPointF delta_viewport_pos = target_viewport_pos - QPointF(_view->viewport()->width() / 2.0,
                                                             _view->viewport()->height() / 2.0);
  QPointF viewport_center = _view->mapFromScene(target_scene_pos) - delta_viewport_pos;
  _view->centerOn(_view->mapToScene(viewport_center.toPoint()));
  emit zoomed();
}

void Graphics_view_zoom::set_modifiers(Qt::KeyboardModifiers modifiers) {
  _modifiers = modifiers;

}

void Graphics_view_zoom::set_zoom_factor_base(double value) {
  _zoom_factor_base = value;
}

bool Graphics_view_zoom::eventFilter(QObject *object, QEvent *event) {
  if (event->type() == QEvent::MouseMove) {
    QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
    QPointF delta = target_viewport_pos - mouse_event->pos();
    if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
      target_viewport_pos = mouse_event->pos();
      target_scene_pos = _view->mapToScene(mouse_event->pos());
    }
  } else if (event->type() == QEvent::Wheel) {
    QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
    if (QApplication::keyboardModifiers() == _modifiers) {
      if (wheel_event->orientation() == Qt::Vertical) {
        double angle = wheel_event->angleDelta().y();
        double factor = qPow(_zoom_factor_base, angle);
        gentle_zoom(factor);
        return true;
      }
    }
  }

  Q_UNUSED(object)
  return false;
}


void Win::_init_view_agents()
{

    QPen pen1(Qt::black);
    QBrush redBrush(Qt::red);
    QBrush blueBrush(Qt::blue);

    panel_view_agents_hbox = new QHBoxLayout();
    panel_view_agents->setLayout(panel_view_agents_hbox);
    graphic_scene = new QGraphicsScene();

    list_of_devices = new QListWidget();
    graphics_view = new CustomGView(graphic_scene);
    graphics_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    graphics_view->setMouseTracking(true);
    graphics_view->setDragMode(QGraphicsView::ScrollHandDrag);
    graphics_view->installEventFilter(this);
    graphics_view->resetMatrix();
    graphics_view->scale(1, 1);

    Graphics_view_zoom *z = new Graphics_view_zoom(graphics_view);
    z->set_modifiers(Qt::NoModifier);

    panel_view_agents_hbox->addWidget(list_of_devices, 1);
    panel_view_agents_hbox->addWidget(graphics_view, 5);

}
