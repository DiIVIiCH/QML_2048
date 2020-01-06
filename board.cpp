#include "board.h"
#include <random>
#include <QtDebug>
Board::Board(size_t game_dimension, QObject *parent):
	QAbstractTableModel {parent},
	m_board_dimension {game_dimension},
	m_highscore{0}
{
	board = std::vector<std::vector<int>>(m_board_dimension, std::vector<int>(m_board_dimension, 0));
	start_game();
}

int Board::rowCount(const QModelIndex &) const
{
	return m_board_dimension;
}

int Board::columnCount(const QModelIndex &) const
{
	return m_board_dimension;
}

QVariant Board::data(const QModelIndex &index, int role) const
{
	switch (role) {
	case Qt::DisplayRole:
		return board[index.row()][index.column()];
	default:
		break;
	}

	return QVariant();
}

void Board::start_game()
{
	board = std::vector<std::vector<int>>(m_board_dimension, std::vector<int>(m_board_dimension, 0));
	m_highscore = 0;
	place_tile();
	place_tile();
	emit dataChanged(createIndex(0,0), createIndex(m_board_dimension, m_board_dimension));
}

void Board::move(Qt::Key key)
{
	switch (key) {
		case Qt::Key::Key_Left: move_left(); break;
		case Qt::Key::Key_Right: move_right(); break;
		case Qt::Key::Key_Up: move_up(); break;
		case Qt::Key::Key_Down: move_down(); break;
	}

	if (is_changed){
		qDebug() << m_highscore;
		if (can_move()){
			place_tile();
		}
		else{
			end_game();
		}
		is_changed = false;
		emit dataChanged(createIndex(0,0), createIndex(m_board_dimension, m_board_dimension));
	}
}

void Board::move_left()
{
	for (size_t i=0; i<m_board_dimension; ++i){
		for (size_t j=0; j<m_board_dimension-1; ++j){
			if (board[i][j]>0){
				for (size_t k=j+1; k<m_board_dimension; ++k){
					if (board[i][k]>0){
						if (board[i][j] == board[i][k]){
							board[i][j] *= 2;
							board[i][k] = 0;
							m_highscore += board[i][j];
							is_changed = true;
						}
						break;
					}
				}
			}
		} // add numbers
		for (size_t j=0; j<m_board_dimension-1; ++j){
			if (board[i][j]==0){
				for (size_t k=j+1; k<m_board_dimension; ++k){
					if (board[i][k] != 0){
						board[i][j] = board[i][k];
						board[i][k] = 0;
						is_changed = true;
						break;
					}
				}
			}
		} // move numbers
	}

}

void Board::move_right()
{
	for (size_t i=0; i<m_board_dimension; ++i){
		for (size_t j=m_board_dimension-1; j>0; --j){
			if (board[i][j]>0){
				for (int k=j-1; k>=0; --k){
					if (board[i][k]>0){
						if (board[i][j] == board[i][k]){
							board[i][j] *= 2;
							board[i][k] = 0;
							m_highscore += board[i][j];
							is_changed = true;
						}
						break;
					}
				}
			}
		} // add numbers
		for (size_t j=m_board_dimension-1; j>0; --j){
			if (board[i][j]==0){
				for (int k=j-1; k>=0; --k){
					if (board[i][k] != 0){
						board[i][j] = board[i][k];
						board[i][k] = 0;
						is_changed = true;
						break;
					}
				}
			}
		} // move numbers
	}

}

void Board::move_up()
{
	for (size_t i=0; i<m_board_dimension; ++i){
		for (size_t j=0; j<m_board_dimension-1; ++j){
			if (board[j][i]>0){
				for (size_t k=j+1; k<m_board_dimension; ++k){
					if (board[k][i]>0){
						if (board[j][i] == board[k][i]){
							board[j][i] *= 2;
							board[k][i] = 0;
							m_highscore += board[j][i];
							is_changed = true;
						}
						break;
					}
				}
			}
		} // add numbers
		for (size_t j=0; j<m_board_dimension-1; ++j){
			if (board[j][i]==0){
				for (size_t k=j+1; k<m_board_dimension; ++k){
					if (board[k][i] != 0){
						board[j][i] = board[k][i];
						board[k][i] = 0;
						is_changed = true;
						break;
					}
				}
			}
		} // move numbers
	}
}

void Board::move_down()
{
	for (size_t i=0; i<m_board_dimension; ++i){
		for (size_t j=m_board_dimension-1; j>0; --j){
			if (board[j][i]>0){
				for (int k=j-1; k>=0; --k){
					if (board[k][i]>0){
						if (board[j][i] == board[k][i]){
							board[j][i] *= 2;
							board[k][i] = 0;
							m_highscore += board[j][i];
							is_changed = true;
						}
						break;
					}
				}
			}
		} // add numbers
		for (size_t j=m_board_dimension-1; j>0; --j){
			if (board[j][i]==0){
				for (int k=j-1; k>=0; --k){
					if (board[k][i] != 0){
						board[j][i] = board[k][i];
						board[k][i] = 0;
						is_changed = true;
						break;
					}
				}
			}
		} // move numbers
	}

}

void Board::end_game()
{

}

bool Board::is_board_full()
{
	for (auto &row: board){
		for (auto &cell: row){
			if (cell==0){
				return false;
			}
		}
	}
	return true;
}

void Board::place_tile()
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::mt19937 g(seed);

	static std::uniform_int_distribution<> d_int(0, m_board_dimension-1);
	static std::uniform_real_distribution<> d_float(0, 1);

	while (1){
		int i = d_int(g);
		int j = d_int(g);
		if (board[i][j]==0){
			board [i][j] = 	d_float(g) < 0.9 ? 2:4;
			break;
		}
	}
}

bool Board::can_move()
{
	if (is_board_full()){
		for (size_t i=0; i<m_board_dimension-1; ++i){
			for (size_t j=0; j<m_board_dimension-1; ++j){
				if (board[i][j]==board[i][j+1]){ return true; }
				if (board[i][j]==board[i+1][j]){ return true; }
			}
		}
		return false;
	}
	return true;
}

size_t Board::highscore() const
{
	return m_highscore;
}



