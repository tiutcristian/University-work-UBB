from ga.encoding.BinaryEncoder import BinaryEncoder
from ga.encoding.RealEncoder import RealEncoder


def get_encoder(x_bounds, y_bounds, config):
    if config["encoding"] == "real":
        return RealEncoder(x_bounds, y_bounds, config)
    return BinaryEncoder(x_bounds, y_bounds, config)