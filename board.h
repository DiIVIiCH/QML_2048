#ifndef BOARD_H
#define BOARD_H
#include <QAbstractTableModel>
#include <vector>

class Board: public QAbstractTableModel
{

	Q_OBJECT
	Q_PROPERTY(int dimension READ rowCount CONSTANT)
	Q_PROPERTY(int highscore READ highscore NOTIFY highscore_changed)
	Q_PROPERTY(int game_active READ game_active NOTIFY game_status_changed)

	Q_ENUMS(Roles)
public:
	enum Roles {
		DisplayRole = Qt::DisplayRole,
		NewCell = Qt::UserRole+1,
		UpdateCell,

	};

	QHash<int, QByteArray> roleNames() const override {
		return {
			{ {Roles::DisplayRole, "display"},
				{Roles::NewCell, "new_cell"},
				{Roles::UpdateCell, "update_role"}
			}
		};
	}

	static constexpr int DEFAULT_DIMENSION {4};

	explicit Board(size_t game_dimension = DEFAULT_DIMENSION, QObject *parent = nullptr);

	int rowCount(const QModelIndex & = QModelIndex()) const override;

	int columnCount(const QModelIndex & = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role) const override;

	Q_INVOKABLE void start_game();

	Q_INVOKABLE void move(Qt::Key key);
	Q_INVOKABLE void move_left();
	Q_INVOKABLE void move_right();
	Q_INVOKABLE void move_up();
	Q_INVOKABLE void move_down();
	Q_INVOKABLE void end_game();

	size_t highscore() const;	
	bool game_active() const;

signals:
	void highscore_changed();
	void game_status_changed();

private:

	bool is_changed = true;

	bool is_board_full();
	void place_tile();
	bool can_move();

	size_t m_board_dimension;
	size_t m_highscore;
	bool m_game_active;
	std::vector<std::vector<int>> board;
	std::vector<std::vector<bool>> new_cells, update_cells;
};

#endif // BOARD_H
