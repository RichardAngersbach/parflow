import pystencils as ps

from pystencilssfg import SfgConfig

def configure_sfg(cfg: SfgConfig):
    cfg.extensions.header = "h"
    cfg.extensions.impl = "cpp"
    cfg.c_interfacing = True
    cfg.header_only = True

def project_info():
    return {
        "project_name": "pystencils_coupling",
        "default_dtype": "float64",
        "use_cpu": True,
        "use_cuda": False,
        "use_openmp": False,
        "target": ps.Target.GenericCPU,
    }