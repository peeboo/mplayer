#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../config.h"
#include "../mp_msg.h"

#ifdef HAVE_XVID

#include "codec-cfg.h"
#include "stream.h"
#include "demuxer.h"
#include "stheader.h"

#include "aviwrite.h"

#include "img_format.h"
#include "mp_image.h"
#include "vf.h"

#include <xvid.h>
#include "xvid_vbr.h"

#include "cfgparser.h"


#ifdef XVID_API_UNSTABLE
#warning *******************************************************************
#warning **                                                               **
#warning **  Y O U '' R E   U S I N G   U N S T A B L E   S O F T W A R E  **
#warning **                                                               **
#warning ** Streams produced by this version aren''nt probably compatible  **
#warning ** with anything else, even the xvid decoder itself. There are   **
#warning ** bugs, this code could crash, could blow up your PC or the     **
#warning ** whole building !                                              **
#warning ** If you want stable code and compatible streams, use stable    **
#warning ** XViD releases (currently 0.9.x).                              **
#warning **                                                               **
#warning *******************************************************************
#endif

/**********************************************************************/
/* motion estimation quality presets */
static int const motion_presets[7] = {
#ifdef XVID_API_UNSTABLE
	0,
	PMV_QUICKSTOP16,
	0,
	0,
	PMV_HALFPELREFINE16 | PMV_HALFPELDIAMOND8,
	PMV_HALFPELREFINE16 | PMV_HALFPELDIAMOND8 | PMV_ADVANCEDDIAMOND16,
	PMV_HALFPELREFINE16 | PMV_EXTSEARCH16 | PMV_HALFPELREFINE8 | PMV_HALFPELDIAMOND8 | PMV_USESQUARES16
#else
        0,
	PMV_QUICKSTOP16,
	PMV_EARLYSTOP16,
	PMV_EARLYSTOP16 | PMV_EARLYSTOP8,
        PMV_EARLYSTOP16 | PMV_HALFPELREFINE16 | PMV_EARLYSTOP8 | PMV_HALFPELDIAMOND8,
        PMV_EARLYSTOP16 | PMV_HALFPELREFINE16 | PMV_EARLYSTOP8 | PMV_HALFPELDIAMOND8 | PMV_ADVANCEDDIAMOND16,
	PMV_EARLYSTOP16 | PMV_HALFPELREFINE16 | PMV_EXTSEARCH16 | PMV_EARLYSTOP8 | PMV_HALFPELREFINE8 | 
	PMV_HALFPELDIAMOND8 | PMV_USESQUARES16

#endif
};

extern char* passtmpfile;
extern void mencoder_write_chunk(aviwrite_stream_t *s,int len,unsigned int flags);

static int xvidenc_pass = 0;
static int xvidenc_quality = 4;
static int xvidenc_4mv = 0;
static int xvidenc_bitrate = -1;
static int xvidenc_rc_reaction_delay_factor = -1;
static int xvidenc_rc_averaging_period = -1;
static int xvidenc_rc_buffer = -1;
static char* xvidenc_quant_range = "2-31/2-31";
static int xvidenc_min_key_interval = -1;
static int xvidenc_max_key_interval = -1;
static int xvidenc_mpeg_quant = 0;
static int xvidenc_mod_quant = 0;
static int xvidenc_lumi_mask = 0;
static int xvidenc_keyframe_boost = -1;
static int xvidenc_kfthreshold = -1;
static int xvidenc_kfreduction = -1;
static int xvidenc_fixed_quant = 0;
static int xvidenc_debug = 0;
static int xvidenc_hintedme = 0;
static char* xvidenc_hintfile = "xvid_hint_me.dat";
#ifdef XVID_API_UNSTABLE
static int xvidenc_qpel = 0;
static int xvidenc_max_bframes = 0;
static int xvidenc_bquant_ratio = 125;
static int xvidenc_bquant_offset = 60;
static int xvidenc_gmc = 0;
static int xvidenc_me_colour = 0;
static int xvidenc_reduced = 0;
#endif

struct config xvidencopts_conf[] = {
    { "pass", &xvidenc_pass, CONF_TYPE_INT, CONF_RANGE, 0, 2, NULL},
    { "me_quality", &xvidenc_quality, CONF_TYPE_INT, CONF_RANGE, 0,
      sizeof(motion_presets) / sizeof(motion_presets[0]) - 1, NULL},
    { "4mv", &xvidenc_4mv, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "bitrate", &xvidenc_bitrate, CONF_TYPE_INT, CONF_RANGE, 4, 24000000, NULL},
    { "rc_reaction_delay_factor", &xvidenc_rc_reaction_delay_factor, CONF_TYPE_INT, 0, 0, 0, NULL},
    { "rc_averaging_period", &xvidenc_rc_averaging_period, CONF_TYPE_INT, 0, 0, 0, NULL},
    { "rc_buffer", &xvidenc_rc_buffer, CONF_TYPE_INT, 0, 0, 0, NULL},
    { "quant_range", &xvidenc_quant_range, CONF_TYPE_STRING, 0, 0, 0, NULL},
    { "min_key_interval", &xvidenc_min_key_interval, CONF_TYPE_INT, 0, 0, 0, NULL}, /* for XVID_MODE_2PASS_2 */
    { "max_key_interval", &xvidenc_max_key_interval, CONF_TYPE_INT, 0, 0, 0, NULL},
    { "mpeg_quant", &xvidenc_mpeg_quant, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "mod_quant", &xvidenc_mod_quant, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "lumi_mask", &xvidenc_lumi_mask, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "keyframe_boost", &xvidenc_keyframe_boost, CONF_TYPE_INT, CONF_RANGE, 0, 1000, NULL}, /* for XVID_MODE_2PASS_2 */
    { "kfthreshold", &xvidenc_kfthreshold, CONF_TYPE_INT, 0, 0, 0, NULL}, /* for XVID_MODE_2PASS_2 */
    { "kfreduction", &xvidenc_kfreduction, CONF_TYPE_INT, CONF_RANGE, 0, 100, NULL}, /* for XVID_MODE_2PASS_2 */
    { "fixed_quant", &xvidenc_fixed_quant, CONF_TYPE_INT, CONF_RANGE, 1, 31, NULL}, /* for XVID_MODE_FIXED_QUANT */
    { "debug", &xvidenc_debug, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "hintedme", &xvidenc_hintedme, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "hintfile", &xvidenc_hintfile, CONF_TYPE_STRING, 0, 0, 0, NULL},
#ifdef XVID_API_UNSTABLE
    { "qpel", &xvidenc_qpel, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "max_bframes", &xvidenc_max_bframes, CONF_TYPE_INT, CONF_RANGE, 0, 4, NULL},
    { "bquant_ratio", &xvidenc_bquant_ratio, CONF_TYPE_INT, CONF_RANGE, 0, 1000, NULL},
    { "bquant_offset", &xvidenc_bquant_offset, CONF_TYPE_INT, CONF_RANGE, -1000, 1000, NULL},
    { "reduced", &xvidenc_reduced, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "gmc", &xvidenc_gmc, CONF_TYPE_FLAG, 0, 0, 1, NULL},
    { "me_colour", &xvidenc_me_colour, CONF_TYPE_FLAG, 0, 0, 1, NULL},
#endif
    { NULL, NULL, 0, 0, 0, 0, NULL}
};

struct vf_priv_s {
    aviwrite_stream_t* mux;
    XVID_ENC_FRAME enc_frame;
    void* enc_handle;
    vbr_control_t vbr_state;
    FILE *hintfile;
    void *hintstream;
};

static int
config(struct vf_instance_s* vf,
       int width, int height, int d_width, int d_height,
       unsigned int flags, unsigned int outfmt)
{
    XVID_ENC_PARAM enc_param;
    struct vf_priv_s *fp = vf->priv;
    unsigned int min_iq, max_iq, min_pq, max_pq;

    fp->mux->bih->biWidth = width;
    fp->mux->bih->biHeight = height;
    fp->mux->bih->biSizeImage = fp->mux->bih->biWidth * fp->mux->bih->biHeight * 3;
    mp_msg(MSGT_MENCODER,MSGL_INFO,"videocodec: XViD (%dx%d fourcc=%x [%.4s])\n",
	width, height, fp->mux->bih->biCompression, (char *)&fp->mux->bih->biCompression);

    // {min,max}_{i,p}quantizer parsing & validation
    if (sscanf (xvidenc_quant_range, "%u-%u/%u-%u", &min_iq, &max_iq, &min_pq, &max_pq) < 4) {
	mp_msg (MSGT_MENCODER, MSGL_ERR, 
		"xvid: ERROR: cannot parse \"quant_range=%s\"\n", xvidenc_quant_range);
	return 0;
    }
    if (min_iq < 1 || min_iq > 31 || max_iq < 1 || max_iq > 31 || min_iq > max_iq ||
	min_pq < 1 || min_pq > 31 || max_pq < 1 || max_pq > 31 || min_pq > max_pq) {
	mp_msg (MSGT_MENCODER, MSGL_ERR,
		"xvid: ERROR: {min,max} {I,P} quantizer must be in [1,31] and min must be <= max.\n");
	mp_msg (MSGT_MENCODER, MSGL_ERR,
		"xvid: ERROR: cannot use \"quant_range=%s\"\n", xvidenc_quant_range);
	return -1;
    }

#ifdef XVID_API_UNSTABLE
    mp_msg (MSGT_MENCODER, MSGL_WARN,
	    "\n"
	    "*******************************************************************\n"
	    "**                                                               **\n"
	    "**  Y O U ' R E   U S I N G   U N S T A B L E   S O F T W A R E  **\n"
	    "**                                                               **\n"
	    "** Streams produced by this version aren'nt probably compatible  **\n"
	    "** with anything else, even the xvid decoder itself. There are   **\n"
	    "** bugs, this code could crash, could blow up your PC or the     **\n"
	    "** whole building !                                              **\n"
	    "** If you want stable code and compatible streams, use stable    **\n"
	    "** XViD releases (currently 0.9.x).                              **\n"
	    "**                                                               **\n"
	    "*******************************************************************\n"
	    "\n");
#endif

    // initialize XViD core parameters
    // ===============================
    memset(&enc_param, 0, sizeof(enc_param));
    enc_param.width = width;
    enc_param.height = height;
    enc_param.fincr = fp->mux->h.dwScale;
    enc_param.fbase = fp->mux->h.dwRate;
    if (xvidenc_bitrate > 16000)
	enc_param.rc_bitrate = xvidenc_bitrate;
    else if (xvidenc_bitrate > 0)
	enc_param.rc_bitrate = xvidenc_bitrate * 1000;
    else
	enc_param.rc_bitrate = -1;
#ifdef XVID_API_UNSTABLE
    if (xvidenc_max_bframes >= 1 && xvidenc_pass >= 1) {
	mp_msg(MSGT_MENCODER,MSGL_WARN, "xvid: cannot use bframes with 2-pass, disabling bframes\n");
	xvidenc_max_bframes = 0;
    }
    enc_param.max_bframes = xvidenc_max_bframes;
    enc_param.bquant_ratio = xvidenc_bquant_ratio;
    enc_param.bquant_offset = xvidenc_bquant_offset;
    if (xvidenc_reduced)
	enc_param.global |= XVID_GLOBAL_REDUCED;
#endif
    enc_param.rc_reaction_delay_factor = xvidenc_rc_reaction_delay_factor;
    enc_param.rc_averaging_period = xvidenc_rc_averaging_period;
    enc_param.rc_buffer = xvidenc_rc_buffer;
    enc_param.min_quantizer = min_iq;
    enc_param.max_quantizer = max_iq;
    if( xvidenc_max_key_interval <= 0 )
	xvidenc_max_key_interval = 10 * enc_param.fbase / enc_param.fincr;
    enc_param.max_key_interval = xvidenc_max_key_interval;
    switch (xvid_encore(NULL, XVID_ENC_CREATE, &enc_param, NULL)) {
    case XVID_ERR_FAIL:
	mp_msg(MSGT_MENCODER,MSGL_ERR, "xvid: encoder creation failed\n");
	return 0;
    case XVID_ERR_MEMORY:
	mp_msg(MSGT_MENCODER,MSGL_ERR, "xvid: encoder creation failed, out of memory\n");
	return 0;
    case XVID_ERR_FORMAT:
	mp_msg(MSGT_MENCODER,MSGL_ERR, "xvid: encoder creation failed, bad format\n");
	return 0;
    }
    fp->enc_handle = enc_param.handle;

    // initialize XViD per-frame static parameters
    // ===========================================
    fp->enc_frame.motion = motion_presets[xvidenc_quality];
    fp->enc_frame.general = XVID_HALFPEL | (xvidenc_mpeg_quant ? XVID_MPEGQUANT : XVID_H263QUANT);
    if (xvidenc_4mv)
	fp->enc_frame.general |= XVID_INTER4V;
    if (xvidenc_lumi_mask)
	fp->enc_frame.general |= XVID_LUMIMASKING;
#ifdef XVID_API_UNSTABLE
    if (xvidenc_qpel) {
	fp->enc_frame.general |= XVID_QUARTERPEL;
	fp->enc_frame.motion |= PMV_QUARTERPELREFINE16 | PMV_QUARTERPELREFINE8;
    }
    if (xvidenc_gmc)
	fp->enc_frame.general |= XVID_GMC;
    if (xvidenc_me_colour)
	fp->enc_frame.general |= XVID_ME_COLOUR;
    if(xvidenc_reduced)
	fp->enc_frame.general |= XVID_REDUCED;
#endif

    switch (outfmt) {
    case IMGFMT_YV12:
	fp->enc_frame.colorspace = XVID_CSP_YV12;
	break;
    case IMGFMT_IYUV: case IMGFMT_I420:
	fp->enc_frame.colorspace = XVID_CSP_I420;
	break;
    case IMGFMT_YUY2:
	fp->enc_frame.colorspace = XVID_CSP_YUY2;
	break;
    case IMGFMT_UYVY:
	fp->enc_frame.colorspace = XVID_CSP_UYVY;
	break;
    case IMGFMT_RGB24: case IMGFMT_BGR24:
    	fp->enc_frame.colorspace = XVID_CSP_RGB24;
	break;
    default:
	mp_msg(MSGT_MENCODER,MSGL_ERR,"xvid: unsupported picture format (%s)!\n",
	       vo_format_name(outfmt));
	return 0;
    }
    fp->enc_frame.quant_intra_matrix = 0;
    fp->enc_frame.quant_inter_matrix = 0;

    // hinted ME
    fp->hintstream = NULL;
    fp->hintfile = NULL;
    if (xvidenc_hintedme && (xvidenc_pass == 1 || xvidenc_pass == 2)) {
	fp->hintstream = malloc( 100000 ); // this is what the vfw code in XViD CVS allocates
	if (fp->hintstream == NULL)
	    mp_msg(MSGT_MENCODER,MSGL_ERR, "xvid: cannot allocate memory for hinted ME\n");
	else {
	    fp->hintfile = fopen(xvidenc_hintfile, xvidenc_pass == 1 ? "w" : "r");
	    if (fp->hintfile == NULL) {
		mp_msg(MSGT_MENCODER,MSGL_ERR, "xvid: %s: %s\n", strerror(errno), xvidenc_hintfile);
		free(fp->hintstream);
	    }
	}
	if (fp->hintstream == NULL || fp->hintfile == NULL)
	    xvidenc_hintedme = 0;
    }

    // initialize VBR engine
    // =====================
    vbrSetDefaults(&fp->vbr_state);
    if (xvidenc_min_key_interval < 0)
	xvidenc_min_key_interval = fp->vbr_state.min_key_interval;

    // pass
    if (xvidenc_pass == 0) {
	if (xvidenc_fixed_quant >= 1) {
	    fp->vbr_state.mode = VBR_MODE_FIXED_QUANT;
	    fp->vbr_state.fixed_quant = xvidenc_fixed_quant;
	} else
	    fp->vbr_state.mode = VBR_MODE_1PASS;
    }
    else if (xvidenc_pass == 1)
	fp->vbr_state.mode = VBR_MODE_2PASS_1;
    else if (xvidenc_pass == 2)
	fp->vbr_state.mode = VBR_MODE_2PASS_2;
    else
	return -1;

    // misc
    fp->vbr_state.fps = (double)enc_param.fbase / enc_param.fincr;
    fp->vbr_state.filename = passtmpfile;
    fp->vbr_state.desired_bitrate = enc_param.rc_bitrate;
    fp->vbr_state.min_iquant = min_iq;
    fp->vbr_state.max_iquant = max_iq;
    fp->vbr_state.min_pquant = min_pq;
    fp->vbr_state.max_pquant = max_pq;
    if (xvidenc_keyframe_boost >= 0)
	fp->vbr_state.keyframe_boost = xvidenc_keyframe_boost;
    if (xvidenc_kfthreshold >= 0)
	fp->vbr_state.kftreshold = xvidenc_kfthreshold;
    if (xvidenc_kfreduction >= 0)
	fp->vbr_state.kfreduction = xvidenc_kfreduction;
    if (xvidenc_min_key_interval >= 0)
	fp->vbr_state.min_key_interval = xvidenc_min_key_interval;
    fp->vbr_state.max_key_interval = enc_param.max_key_interval;
    fp->vbr_state.debug = xvidenc_debug;

    vbrInit(&fp->vbr_state);

    return 1;
}

static void
uninit(struct vf_instance_s* vf)
{
    struct vf_priv_s *fp = vf->priv;

    if (fp->hintfile)
	fclose(fp->hintfile);
    if (fp->hintstream)
	free(fp->hintstream);
    vbrFinish(&fp->vbr_state);
}

static int
control(struct vf_instance_s* vf, int request, void* data)
{
    return CONTROL_UNKNOWN;
}

static int
query_format(struct vf_instance_s* vf, unsigned int fmt)
{
    switch(fmt){
    case IMGFMT_YV12: case IMGFMT_IYUV: case IMGFMT_I420:
	return VFCAP_CSP_SUPPORTED | VFCAP_CSP_SUPPORTED_BY_HW;
    case IMGFMT_YUY2: case IMGFMT_UYVY:
	return VFCAP_CSP_SUPPORTED;
    case IMGFMT_RGB24: case IMGFMT_BGR24:
	return VFCAP_CSP_SUPPORTED | VFCAP_FLIPPED;
    }
    return 0;
}

static int
put_image(struct vf_instance_s* vf, mp_image_t *mpi)
{
    XVID_ENC_STATS enc_stats;
    struct vf_priv_s *fp = vf->priv;

    fp->enc_frame.bitstream = fp->mux->buffer;
    fp->enc_frame.length = -1 /* fp->mux->buffer_size */;
    fp->enc_frame.image = mpi->planes[0];

    // get quantizers & I/P decision from the VBR engine
#ifdef XVID_API_UNSTABLE
    if (xvidenc_max_bframes >= 1) {
	if (!xvidenc_fixed_quant) {
	    // hack, the internal VBR engine isn't fixed-quant aware
	    fp->enc_frame.quant = xvidenc_fixed_quant;
	    fp->enc_frame.intra = -1;
	    fp->enc_frame.bquant = (xvidenc_fixed_quant * xvidenc_bquant_ratio + xvidenc_bquant_offset) / 100;
	} else
	    // use the internal VBR engine since the external one isn't bframe aware
	    fp->enc_frame.quant = fp->enc_frame.intra = fp->enc_frame.bquant = -1;
    } else {
	fp->enc_frame.quant = vbrGetQuant(&fp->vbr_state);
	fp->enc_frame.intra = vbrGetIntra(&fp->vbr_state);
    }
#else
    fp->enc_frame.quant = vbrGetQuant(&fp->vbr_state);
    fp->enc_frame.intra = vbrGetIntra(&fp->vbr_state);
#endif

    // modulated quantizer type
    if (xvidenc_mod_quant && xvidenc_pass == 2) {
	fp->enc_frame.general |= (fp->enc_frame.quant < 4) ? XVID_MPEGQUANT : XVID_H263QUANT;
	fp->enc_frame.general &= (fp->enc_frame.quant < 4) ? ~XVID_H263QUANT : ~XVID_MPEGQUANT;
    }

    // hinted ME, 1st part
    if (xvidenc_hintedme && xvidenc_pass == 1) {
	fp->enc_frame.hint.hintstream = fp->hintstream;
	fp->enc_frame.hint.rawhints = 0;
	fp->enc_frame.general |= XVID_HINTEDME_GET;
    }
    else if (xvidenc_hintedme && xvidenc_pass == 2) {
	size_t read;
	int blocksize;
	fp->enc_frame.general &= ~XVID_HINTEDME_SET;
	read = fread(&blocksize, sizeof(blocksize), 1, fp->hintfile);
	if (read == 1) {
	    read = fread(fp->hintstream, (size_t)blocksize, 1, fp->hintfile);
	    if (read == 1) {
		fp->enc_frame.hint.hintstream = fp->hintstream;
		fp->enc_frame.hint.hintlength = 0;
		fp->enc_frame.hint.rawhints = 0;
		fp->enc_frame.general |= XVID_HINTEDME_SET;
	    } 
	    else
		perror("xvid: hint file read block failure");
	} 
	else
	    perror("xvid: hint file read failure");
    }

    // encode frame
    switch (xvid_encore(fp->enc_handle, XVID_ENC_ENCODE, &fp->enc_frame, &enc_stats)) {
    case XVID_ERR_OK:
	break;
    case XVID_ERR_MEMORY:
	mp_msg(MSGT_MENCODER, MSGL_ERR, "xvid: out of memory\n");
	break;
    case XVID_ERR_FORMAT:
	mp_msg(MSGT_MENCODER, MSGL_ERR, "xvid: bad format\n");
	break;
    default:
	mp_msg(MSGT_MENCODER, MSGL_ERR, "xvid: failure\n");
	break;
    }
    
    // write output
    mencoder_write_chunk(fp->mux, fp->enc_frame.length, fp->enc_frame.intra==1 ? 0x10 : 0);

    // update the VBR engine
    vbrUpdate(&fp->vbr_state, enc_stats.quant, fp->enc_frame.intra,
	      enc_stats.hlength, fp->enc_frame.length, enc_stats.kblks, enc_stats.mblks, enc_stats.ublks);

    // hinted ME, 2nd part
    if (fp->enc_frame.general & XVID_HINTEDME_GET) {
	size_t wrote = fwrite(&fp->enc_frame.hint.hintlength, sizeof(fp->enc_frame.hint.hintlength), 1, fp->hintfile);
	if (wrote == 1) {
	    wrote = fwrite(fp->enc_frame.hint.hintstream, fp->enc_frame.hint.hintlength, 1, fp->hintfile);
	    if (wrote != 1)
		perror("xvid: hint write block failure");
	}
	else
	    perror("xvid: hint write failure");
    }
    return 1;
}

//===========================================================================//

static int
vf_open(vf_instance_t *vf, char* args)
{
    XVID_INIT_PARAM params = { 0, 0, 0};
    vf->config = config;
    vf->control = control;
    vf->uninit = uninit;
    vf->query_format = query_format;
    vf->put_image = put_image;
    vf->priv = malloc(sizeof(struct vf_priv_s));
    memset(vf->priv, 0, sizeof(struct vf_priv_s));
    vf->priv->mux = (aviwrite_stream_t*)args;

    vf->priv->mux->bih = malloc(sizeof(BITMAPINFOHEADER));
    vf->priv->mux->bih->biSize = sizeof(BITMAPINFOHEADER);
    vf->priv->mux->bih->biWidth = 0;
    vf->priv->mux->bih->biHeight = 0;
    vf->priv->mux->bih->biPlanes = 1;
    vf->priv->mux->bih->biBitCount = 24;
    vf->priv->mux->bih->biCompression = mmioFOURCC('X','V','I','D');

    if (xvid_init(NULL, 0, &params, NULL) != XVID_ERR_OK) {
	mp_msg(MSGT_MENCODER,MSGL_ERR, "xvid: initialisation failure\n");
	abort();
    }
    if (params.api_version != API_VERSION) {
	mp_msg(MSGT_MENCODER,MSGL_ERR, "xvid: XviD library API version mismatch\n"
		"\texpected %d.%d, got %d.%d, you should recompile MPlayer.\n",
		API_VERSION >> 16, API_VERSION & 0xff,
		params.api_version >> 16, params.api_version & 0xff);
	abort();
    }

    return 1;
}

vf_info_t ve_info_xvid = {
    "XviD encoder",
    "xvid",
    "Kim Minh Kaplan & R�mi Guyomarch",
    "for internal use by mencoder",
    vf_open
};

//===========================================================================//
#endif
