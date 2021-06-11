site_configuration = {
    'systems': [
        {
            'name': 'dine',
            'descr': 'DINE',
            'hostnames': ['b101.pri.cosma7.alces.network', 'login8a.pri.cosma7.alces.network'],
            'modules_system': 'tmod4',
            'partitions': [
                {
                    'name': 'login',
                    'descr': 'login nodes',
                    'scheduler': 'local',
                    'launcher': 'local',
                    'environs': ['intel'],
                    'max_jobs': 100,
                },
                {
                    'name': 'cpu_single_node_multi_ranks',
                    'descr': 'cpu nodes - single node, multi ranks',
                    'scheduler': 'slurm',
                    'launcher': 'mpirun',
                    'access': ['-p bluefield1', '-A durham'],
                    'environs': ['intel'],
                    'max_jobs': 100,
                },
            ]
        }
    ],
    'environments': [
        {
            'modules': ['gnu_comp/10.2.0',
                        'python/3.6.5'],
             'name': 'intel',
             'cc': 'icc',
             'cxx': 'icpc',
             'ftn': '',
             'target_systems': ['dine'],
             'variables': [['PYTHONPATH','../../../python']]
        },
    ],
    'logging': [
        {
            'level': 'debug',
            'handlers': [
                {
                    'type': 'stream',
                    'name': 'stdout',
                    'level': 'info',
                    'format': '%(message)s'
                },
                {
                    'type': 'file',
                    'name': 'reframe.log',
                    'level': 'debug',
                    'format': '[%(asctime)s] %(levelname)s: %(check_info)s: %(message)s',   # noqa: E501
                    'append': False
                }
            ],
            'handlers_perflog': [
                {
                    'type': 'filelog',
                    'prefix': '%(check_system)s/%(check_partition)s',
                    'level': 'info',
                    'format': (
                        '%(check_job_completion_time)s|reframe %(version)s|'
                        '%(check_info)s|jobid=%(check_jobid)s|'
                        '%(check_perf_var)s=%(check_perf_value)s|'
                        'ref=%(check_perf_ref)s '
                        '(l=%(check_perf_lower_thres)s, '
                        'u=%(check_perf_upper_thres)s)|'
                        '%(check_perf_unit)s'
                    ),
                    'append': True
                }
            ]
        }
    ],
}
