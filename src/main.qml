import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
	width: 640
	height: 480
	visible: true
	title: qsTr("Quadratic Root Solver")

	ColumnLayout {
		anchors.fill: parent

		Label {
			id: equation_label
			text: "ax<sup>2</sup> + bx + c = 0"
			textFormat: Label.RichText
		}

		GridLayout {
			id: coefficient_layout
			columns: 2
			Layout.fillWidth: true

			Label {
			 id: a_label
			 text: "a:"
			}

			TextField {
			 id: a_field
			}

			Label {
			 id: b_label
			 text: "b:"
			}

			TextField {
			 id: b_field
			}

			Label {
				id: c_label
				text: "c:"
			}

			TextField {
				id: c_field
			}
		}

		RowLayout {
			id: root_layout
			Layout.fillWidth: true

			Label {
				id: left_root_label
				text: "Roots ("
			}

			TextField {
				id: root1_field
			}

			Label {
				id: center_root_label
				text: ","
			}

			TextField {
				id: root2_field
			}

			Label {
				id: right_root_label
				text: ")"
			}
		}
	}
}
