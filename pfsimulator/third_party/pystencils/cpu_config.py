from pystencilssfg import SfgConfig

def configure_sfg(cfg: SfgConfig):
    cfg.extensions.header = "h"
    cfg.extensions.impl = "cpp"
    cfg.c_interfacing = True

def project_info():
    return {
        "project_name": "pystencils_coupling",
        "float_precision": "float64",
        "use_cuda": False,
    }